/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:38:29 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/13 17:06:42 by OrioPrisc        ###   ########.fr       */
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

static int	init_prompt_loop(char **envp, t_env_ret *env_ret)
{
	if (init_envp_vec(envp, env_ret))
		msh_error("malloc");
	load_in_history(env_ret);
	signal_assign(SIGINT, sigint_handler_parent);
	signal_assign(SIGQUIT, SIG_IGN);
	return (0);
}

/*	
**	readline returns NULL for both Ctrl-d and for EOF (redirection?)
**		how do we differenciate?
**	
**	print_tokens(&owned_tokens);
**/

int	prompt_loop(char **envp)
{
	t_vector		com_list;
	t_vector		owned_tokens;
	t_cominfo		cominfo;
	t_env_ret		env_ret;
	t_ft_rl			rlinfo;

	ft_rl_init(&rlinfo);
	ft_bzero(&cominfo, sizeof(cominfo));
	init_prompt_loop(envp, &env_ret);
	vector_init(&com_list, sizeof(char *));
	cominfo = (t_cominfo){&env_ret, &com_list};
	while (1)
	{
		if (!ft_readline(&rlinfo, "minishell> "))
			msh_exit(&cominfo);
		if (parse_line(rlinfo.line, &owned_tokens, &env_ret, &rlinfo))
			return (1);
		tree_crawler(&owned_tokens, &cominfo);
		history_loop_logic(cominfo.com_list, ft_strdup("TODO REPLACE ME"));
		vector_free(&owned_tokens, free_owned_token);
	}
	return (0);
}

/*
int main(int argc, char **argv, char **epnvp)
{
	t_vector		owned_tokens;
	size_t			i;
	t_owned_token	*token;

	(void)argc;
	(void)argv;
	i = 0;
	if (parse_line(readline("minishell >"), &owned_tokens, env_ret))
		return (1);
	while (i < owned_tokens.size)
	{
		token = ((t_owned_token *)owned_tokens.data) + i;
		printf("%s : %s\n", token_type_to_str(token->type), token->str);
		i++;
	}
}
*/
