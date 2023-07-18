/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 08:03:56 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/18 15:52:17 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include "libft.h"

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
	if (signum)
	{
	}
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*	
**	The signal raised by Ctrl-\ is SIGQUIT
**	Per the subject, this signal should "do nothing".
**/

void	sigquit_handler(int signum)
{
	if (signum)
	{
	}
}
