/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:05:33 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/22 16:03:22 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "get_next_line.h"
#include <readline/history.h>
#include <fcntl.h>
#include <unistd.h>
#include "vector.h"
#include "env_var.h"
#include "path.h"
#include <stdlib.h>
#include "error.h"

/*	
**	TAKES
**		envp, envp variable name, history_filename
**	RETURNS
**		Pointer to malloced string for history file path.
**/

static char	*history_file_path(const t_env_ret *env_ret, const char *envp_var,
						const char *h_fn)
{
	const char	*home;

	home = get_env_var(env_ret, envp_var, ft_strlen(envp_var));
	if (!home || !*home)
	{
		home = (char *)malloc(sizeof(char));
		if (!home)
			return (NULL);
		ft_bzero((void *)home, sizeof(char));
		return ((char *)home);
	}
	return (path_concat(home, h_fn));
}

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

int	load_in_history(const t_env_ret *env_ret)
{
	int		history_fd;
	char	*history_fn;
	char	*gnl_line;

	history_fn = history_file_path(env_ret, HISTORY_FILE_PATH,
			HISTORY_FILE_NAME);
	if (!history_fn)
		return (msh_error("malloc"), -1);
	if (!*history_fn)
		return (free(history_fn), 0);
	history_fd = open(history_fn, O_RDONLY);
	free(history_fn);
	if (history_fd < 2)
		return (0);
	gnl_line = get_next_line(history_fd);
	while (gnl_line)
	{
		if (ft_strchr(gnl_line, '\n'))
			gnl_line[ft_strlen(gnl_line) - 1] = 0;
		add_history(gnl_line);
		free(gnl_line);
		gnl_line = get_next_line(history_fd);
	}
	return (close(history_fd), 0);
}

/*	
**	readline sometimes adds a \n at the of the string if the user arrows through
**	the history, for this reason, we have to check the end of the string in the
**	vector to see if we have a \n then add one if needed to the history file.
**	
**	NOTE:	check this function performs correctly after adding here_doc or other
**			things that may contain newlines.
**	
**/

static int	history_newline_check(const char *str, int history_fd)
{
	if (str[ft_strlen(str)] != '\n' && *str)
	{
		if (write(history_fd, "\n", 1) < 0)
			return (msh_error("write"), -1);
	}
	return (0);
}

/*
**	need history_fn to equal $HOME/.msh_history. would like a clean way to 
**	access $HOME.
*/

int	save_history(const t_env_ret *env_ret, t_vector *com_list)
{
	char	*history_fn;
	int		history_fd;
	size_t	i;

	history_fn = history_file_path(env_ret,
			HISTORY_FILE_PATH, HISTORY_FILE_NAME);
	if (!history_fn)
		return (msh_error("malloc"), -1);
	if (!*history_fn)
		return (free(history_fn), 0);
	history_fd = open(history_fn, O_CREAT | O_WRONLY | O_APPEND, 0666);
	free(history_fn);
	i = 0;
	while (i < com_list->size)
	{
		if (write(history_fd, ((char **)com_list->data)[i],
			ft_strlen(((char **)com_list->data)[i])) < 0)
			return (close(history_fd), msh_error("write"), -1);
		if (history_newline_check(((char **)com_list->data)[i], history_fd))
			break ;
		i++;
	}
	return (close(history_fd), 0);
}

int	history_loop_logic(t_vector *com_list, char *str)
{
	if (*str)
	{
		if (vector_append(com_list, &str))
			return (msh_error("malloc"), -1);
		add_history(str);
	}
	else
		free(str);
	return (0);
}
