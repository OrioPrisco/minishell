/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:38:29 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/07 17:57:44 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	
**	signal returns pointer to most recent function call by signal.
**	returns SIG_ERR in case of error and errno is set.
**	
**	NOTE: you may want to use sigaction rather than signal if you need specific
**	information about the process that is running. The struct with sigaction
**	provides more information than the signal function.
**/

static int	init_prompt_loop(char **env)
{
	void	(*sig_return)(int);

	load_in_history(env);
	sig_return = signal(SIGINT, &sigint_handler);
	if (sig_return == SIG_ERR)
		msh_error("signal error");
	sig_return = signal(SIGQUIT, &sigquit_handler);
	if (sig_return == SIG_ERR)
		msh_error("signal error");
	return (0);
}

/*	
**	readline returns NULL for both Ctrl-d and for EOF (redirection?)
**		how do we differenciate?
**/

int	prompt_loop(char **env)
{
	char		*str_input;
	t_vector	com_list;
	t_token		*tokens;

	init_prompt_loop(env);
	vector_init(&com_list, sizeof(char *));
	while (1)
	{
		str_input = readline("> ");
		if (!str_input)
			msh_exit(env, &com_list);
		tokens = split_to_tokens(str_input);
		print_tokens(tokens);
		ft_printf("return: %d\n", tree_crawler(tokens));
		free(tokens);
		if (*str_input)
		{
			if (vector_append(&com_list, &str_input))
				msh_error("malloc");
			add_history(str_input);
		}
	}
	return (0);
}
