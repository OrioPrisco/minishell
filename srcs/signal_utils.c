/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 08:03:56 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/19 16:10:05 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include "libft.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "msh_signal.h"

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

volatile int	g_sig_triggered;

void	sigint_handler_parent(int signum)
{
	(void) signum;
	g_sig_triggered = PARENT_SIGINT;
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

void	sigint_handler_heredoc(int signum)
{
	(void) signum;
	close(STDIN_FILENO);
	g_sig_triggered = HD_SIGINT;
	ft_putstr_fd("\n", 1);
}

int	signal_assign(int signal, void (*f)(int))
{
	struct sigaction	sa;

	ft_bzero((void *)&sa, sizeof(sa));
	sa.sa_handler = f;
	sa.sa_flags = 0;
	if (sigaction(signal, &sa, NULL) == -1)
		return (perror("sigaction"), -1);
	return (0);
}
