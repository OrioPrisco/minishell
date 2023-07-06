/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:05:33 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/06 14:57:46 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * From online manuals: https://tiswww.case.edu/php/chet/readline/readline.html
 * 				and   : http://www.math.utah.edu/docs/info/hist_2.html
 *
 * Function: void rl_clear_history (void)
 *     Clear the history list by deleting all of the entries, in the same manner
 *     as the History library’s clear_history() function. This differs from
 *     clear_history because it frees private data Readline saves in the history
 *     list. ))
 *
 * Function: int rl_on_new_line (void)
 *     Tell the update functions that we have moved onto a new (empty) line, 
 *     usually after outputting a newline. ))
 *
 * Function: void rl_replace_line (const char *text, int clear_undo)
 *     Replace the contents of rl_line_buffer with text. The point and mark 
 *     are preserved, if possible. If clear_undo is non-zero, the undo list 
 *     associated with the current line is cleared. )
 *
 * Function: void rl_redisplay (void)
 *     Change what’s displayed on the screen to reflect the current contents 
 *     of rl_line_buffer. )
 *
 * Function: void add_history (char *string)
 *     Place string at the end of the history list. The associated data field 
 *     (if any) is set to NULL. ))
 */

bool	load_in_history(void)
{
	int		history_fd;
	char	*history_fn;
	char	*gnl_line;

	history_fn = "/home/drew/.msh_history";
	history_fd = open(history_fn, O_RDONLY);
	if (history_fd < 2)
		return (1);
	gnl_line = get_next_line(history_fd);
	while (gnl_line)
	{
		if (ft_strchr(gnl_line, '\n'))
			gnl_line[ft_strlen(gnl_line)] = 0;
		add_history(gnl_line);
		free(gnl_line);
		gnl_line = get_next_line(history_fd);
	}
	close(history_fd);
	return (0);
}


/*	
**	readline sometimes adds a \n at the of the string if the user arrows through
**	the history, for this reason, we have to check the end of the string in the
**	vector to see if we have a \n then add one if needed to the history file.
**/

static int	history_newline_check(t_vector *com_list, int history_fd, int i)
{
	if (!ft_strchr(((char **)com_list->data)[i], '\n'))
	{
		if (write(history_fd, "\n", 1) < 0)
		{
			close(history_fd);
			msh_error("write");
		}
	}
	return (0);
}

/*
**	need history_fn to equal $HOME/.msh_history. would like a clean way to 
**	access $HOME.
*/

bool	save_history(t_vector *com_list)
{
	char	*history_fn;
	int		history_fd;
	size_t	i;

	history_fn = "/home/drew/.msh_history";
	history_fd = open(history_fn, O_CREAT | O_WRONLY | O_APPEND, 0666);
	i = 0;
	while (i < com_list->size)
	{
		if (write(history_fd, ((char **)com_list->data)[i],
			ft_strlen(((char **)com_list->data)[i])) < 0)
		{
			close(history_fd);
			msh_error("write");
		}
		history_newline_check(com_list, history_fd, i);
		i++;
	}
	close(history_fd);
	return (0);
}