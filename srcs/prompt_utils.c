/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:38:29 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/24 18:16:27 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "vector.h"
#include "tokens.h"
#include "utils.h"
#include "env_var.h"
#include <signal.h>
#include "ft_readline.h"
#include "msh_signal.h"
#include "parser.h"
#include "error.h"
#include <stdlib.h>

static int	init_envp_vec(char **envp, t_env_ret *env_ret)
{
	int			i;
	char		*buf;
	t_vector	*env_vec;

	i = 0;
	env_vec = &env_ret->env_vec;
	vector_init(env_vec, sizeof(char *));
	env_ret->prev_ret = 0;
	while (envp[i])
	{
		buf = ft_strdup(envp[i]);
		if (!buf || vector_append(env_vec, &buf))
			return (free(buf), vector_free(env_vec, free_str), -1);
		i++;
	}
	if (vector_null_term(env_vec))
		return (vector_free(env_vec, free_str), -1);
	return (0);
}

/*	
**	signal returns pointer to most recent function call by signal.
**	returns SIG_ERR in case of error and errno is set.
**	
**	NOTE: you may want to use sigaction rather than signal if you need specific
**	information about the process that is running. The struct with sigaction
**	provides more information than the signal function.
**/

static void	init_prompt_loop(char **envp, t_env_ret *env_ret, t_ft_rl *rlinfo,
				t_cominfo *cominfo)
{
	if (init_envp_vec(envp, env_ret))
		msh_exit(cominfo, 1, 0);
	if (load_in_history(env_ret))
		msh_exit(cominfo, 1, 0);
	signal_assign(SIGINT, sigint_handler_parent);
	signal_assign(SIGQUIT, SIG_IGN);
	ft_rl_init(rlinfo);
	ft_bzero(cominfo, sizeof(*cominfo));
	vector_init(&cominfo->com_list, sizeof(char *));
	cominfo->env_ret = env_ret;
	cominfo->rlinfo = rlinfo;
}

/*	
**	readline returns NULL for both Ctrl-d and for EOF (redirection?)
**		how do we differenciate?
**	
**	print_tokens(&owned_tokens);
**/

// TODO : cal ft_rl_clear on error
// also clear owned_token on history failure
void	prompt_loop(char **envp)
{
	t_vector		owned_tokens;
	t_cominfo		cominfo;
	t_env_ret		env_ret;
	t_ft_rl			rlinfo;
	char			*command;

	init_prompt_loop(envp, &env_ret, &rlinfo, &cominfo);
	while (1)
	{
		g_sig_triggered = NONE;
		if (!ft_readline(&rlinfo, "minishell> "))
			msh_exit(&cominfo, env_ret.prev_ret, 1);
		if (g_sig_triggered == PARENT_SIGINT)
			env_ret.prev_ret = SIGINT_RECEIVED;
		if (parse_line(&command, &owned_tokens, &env_ret, &rlinfo))
			msh_exit(&cominfo, 1, 1);
		if (history_loop_logic(&cominfo.com_list, command))
			return (vector_free(&owned_tokens, free_owned_token),
				free(command), msh_exit(&cominfo, 1, 1));
		if (owned_tokens.size == 0)
			continue ;
		env_ret.prev_ret = tree_crawler(&owned_tokens, &cominfo);
		vector_free(&owned_tokens, free_owned_token);
	}
}
