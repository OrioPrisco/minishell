/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:38:29 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/15 10:29:05 by dpentlan         ###   ########.fr       */
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

static int	init_prompt_loop(char **envp)
{
	void	(*sig_return)(int);

	load_in_history(envp);
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
**	
**	print_tokens(tokens);
**/

int	prompt_loop(char **envp)
{
	char		*str_input;
	t_vector	com_list;
	t_vector	tokens;

	init_prompt_loop(envp);
	vector_init(&com_list, sizeof(char *));
	while (1)
	{
		str_input = readline("> ");
		if (!str_input)
			msh_exit(envp, &com_list);
		if (split_to_tokens(str_input, &tokens))
			perror("Error");
		//tree_crawler(tokens);
		if (*str_input)
		{
			if (vector_append(&com_list, &str_input))
				msh_error("malloc");
			add_history(str_input);
		}
		else
			free(str_input);
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
