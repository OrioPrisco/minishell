/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:38:29 by dpentlan          #+#    #+#             */
/*   Updated: 2023/10/06 17:21:45 by dpentlan         ###   ########.fr       */
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
#include "ft_printf.h"
#include <unistd.h>

int	increase_shlvl(t_env_ret	*env_ret)
{
	long	parsed;
	char	*str;

	parsed = ft_strtol(get_env_varnul(env_ret, "SHLVL", 5), NULL, 10);
	parsed++;
	if (((int)parsed) < 0)
		parsed = 0;
	if (((int)parsed) >= 1000)
	{
		ft_dprintf(2,
			"minishell: warning: shell level (%d) too high, resetting to 1\n",
			(int)parsed);
		parsed = 1;
	}
	str = ft_itoa(parsed);
	if (!str || add_key_value_to_env_vec("SHLVL=", str, &env_ret->env_vec))
		return (free(str), -1);
	return (free(str), 0);
}

static int	init_envp_vec(char **envp, t_env_ret *env_ret)
{
	int			i;
	char		*buf;
	t_vector	*env_vec;
	int			ret;

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
	buf = getcwd(NULL, 0);
	ret = 0;
	if (!buf)
		msh_error("getcwd");
	else
		ret = add_key_value_to_env_vec("PWD=", buf, env_vec);
	if (ret || vector_null_term(env_vec))
		return (free(buf), vector_free(env_vec, free_str), -1);
	return (free(buf), increase_shlvl(env_ret));
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
	signal_assign(SIGINT, sigint_handler_parent);
	signal_assign(SIGQUIT, SIG_IGN);
	ft_rl_init(rlinfo);
	ft_bzero(cominfo, sizeof(*cominfo));
	vector_init(&cominfo->com_list, sizeof(char *));
	cominfo->env_ret = env_ret;
	cominfo->rlinfo = rlinfo;
	if (init_envp_vec(envp, env_ret))
		msh_exit(cominfo, 1, 0);
	if (load_in_history(env_ret))
		msh_exit(cominfo, 1, 0);
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
		if (!ft_readline(&rlinfo, "minishell> ", NULL, sigint_handler_parent))
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
		if (tree_crawler(&owned_tokens, &cominfo))
			msh_exit(&cominfo, 1, 1);
		vector_free(&owned_tokens, free_owned_token);
	}
}
