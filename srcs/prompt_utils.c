/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:38:29 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/05 11:59:05 by dpentlan         ###   ########.fr       */
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

int	init_prompt_loop(void)
{
	void	(*sig_return)(int);

	load_in_history();
	sig_return = signal(SIGINT, &sigint_handler);
	if (sig_return == SIG_ERR)
		msh_error("signal error");
	sig_return = signal(SIGQUIT, &sigquit_handler);
	if (sig_return == SIG_ERR)
		msh_error("signal error");
	return (0);
}

/*	
**	realine returns NULL for both Ctrl-d and for EOF (redirection?)
**		how do we differenciate?
**/

int	prompt_loop(char **env)
{
	char	*str_input;

	init_prompt_loop();
	if (env)
	{
	}
	while (1)
	{
		str_input = readline("> ");
		if (!str_input)
			msh_exit();
		add_com_to_history(str_input);
		add_history(str_input);
		free(str_input);
	}
	return (0);
}
