/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 08:03:56 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/12 16:13:18 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include "libft.h"
#include <signal.h>
#include <stdlib.h>

/*	
**	The signal raised by Ctrl-c is SIGINT
**	Per the subject, this signal should display a new prompt on a new line.
**	
**	Function: void rl_replace_line (const char *text, int clear_undo)
**	    Replace the contents of rl_line_buffer with text. The point and mark 
**	are preserved, if possible. If clear_undo is non-zero, the undo list 
**	associated with the current line is cleared.
**	
**	Function: int rl_redisplay ()
**		Change what's displayed on the screen to reflect the current contents of 
**	rl_line_buffer. 
**	
**	Function: int rl_on_new_line (void)
**	    Tell the update functions that we have moved onto a new (empty) line, 
**	usually after outputting a newline.
**/

void	sigint_handler(int signum)
{
	(void) signum;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler_child(int signum)
{
	(void) signum;
	ft_putstr_fd("\n", 1);
}

void	sigint_child(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler_child;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}

void	sigint_parent(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}

void	sigquit_parent(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}
