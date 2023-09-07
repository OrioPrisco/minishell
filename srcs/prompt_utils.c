/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:38:29 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/07 14:32:51 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <signal.h>
#include "vector.h"
#include "tokens.h"
#include "utils.h"
#include <readline/readline.h>

static int	init_envp_vec(char **envp, t_vector *env_vec)
{
	int			i;
	char		*buf;

	i = 0;
	vector_init(env_vec, sizeof(char *));
	while (envp[i])
	{
		buf = ft_strdup(envp[i]);
		if (!buf || vector_append(env_vec, &buf))
			return (free(buf), vector_free(env_vec, free_str), -1);
		i++;
	}
	vector_null_term(env_vec);
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

static int	init_prompt_loop(char **envp, t_vector *env_vec)
{
	void		(*sig_return)(int);

	load_in_history(envp);
	sig_return = signal(SIGINT, &sigint_handler);
	if (sig_return == SIG_ERR)
		msh_error("signal error");
	sig_return = signal(SIGQUIT, &sigquit_handler);
	if (sig_return == SIG_ERR)
		msh_error("signal error");
	if (init_envp_vec(envp, env_vec))
		msh_error("malloc");
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
	char			*str_input;
	t_vector		com_list;
	t_vector		owned_tokens;
	t_vector		env_vec;
	t_cominfo		cominfo;

	init_prompt_loop(envp, &env_vec);
	vector_init(&com_list, sizeof(char *));
	while (1)
	{
		str_input = readline("minishell> ");
		ft_bzero((void *)&cominfo, sizeof(cominfo));
		cominfo = (t_cominfo){str_input, &env_vec, &com_list};
		if (!str_input)
			msh_exit(&cominfo);
		if (parse_line(str_input, &owned_tokens, (char **)env_vec.data))
			return (1);
		tree_crawler(&owned_tokens, &cominfo);
		history_loop_logic(&cominfo);
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
	if (parse_line(readline("minishell >"), &owned_tokens, envp))
		return (1);
	while (i < owned_tokens.size)
	{
		token = ((t_owned_token *)owned_tokens.data) + i;
		printf("%s : %s\n", token_type_to_str(token->type), token->str);
		i++;
	}
}
*/
