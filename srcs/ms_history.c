/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:05:33 by dpentlan          #+#    #+#             */
/*   Updated: 2023/06/30 12:12:51 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * From online manuals: https://tiswww.case.edu/php/chet/readline/readline.html
 * 				and   : http://www.math.utah.edu/docs/info/hist_2.html
 *
 * Function: void rl_clear_history (void)
 *     Clear the history list by deleting all of the entries, in the same manner as the History library’s clear_history() function. This differs from clear_history because it frees private data Readline saves in the history list. ))
 *
 * Function: int rl_on_new_line (void)
 *     Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline. ))
 *
 * Function: void rl_replace_line (const char *text, int clear_undo)
 *     Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared. )
 *
 * Function: void rl_redisplay (void)
 *     Change what’s displayed on the screen to reflect the current contents of rl_line_buffer. )
 *
 * Function: void add_history (char *string)
 *     Place string at the end of the history list. The associated data field (if any) is set to NULL. ))
 */

int	add_com_to_history(char *str)
{
	int 	history_fd;
	char	*history_fn;

	// need history_fn to equal $HOME/.ms_history. would like a clean way to access $HOME.
	history_fd = open(history_fn, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (history_fd < 2)
		ms_error("open");
	if (write(history_fd, str, ft_strlen(str)))
	{
		close(history_fd);
		ms_error("write");
	}
	close(history_fd);
	return (0);
}
