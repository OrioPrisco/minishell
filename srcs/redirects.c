/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:21:36 by dpentlan          #+#    #+#             */
/*   Updated: 2023/10/05 11:35:12 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirects.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include "tokens.h"
#include "vector.h"
#include <stdlib.h>
#include <stdio.h>
#include "path.h"
#include "error.h"
#include "utils.h"
#include "minishell.h"

/*	
**	dup2 to least greater than or equal to 10
**	
**/

static int	dup_to_lget(t_vector *vec_fds, int fd)
{
	size_t	i;
	int		greatest;
	int		ret;

	i = 0;
	ret = 0;
	greatest = 10;
	while (i < vec_fds->size)
	{
		if (((int *)vec_fds->data)[i] >= greatest)
			greatest = ((int *)vec_fds->data)[i] + 1;
		i++;
	}
	ret = dup2(fd, greatest);
	close(fd);
	if (ret < 0)
		return (ret);
	((int *)vec_fds->data)[vec_fds->size - 1] = greatest;
	return (0);
}

static int	redir_stdout_token_found(t_owned_token *owned_token,
							t_vector *vec_fds, char *fn_start)
{
	int		fd;

	if (is_directory(fn_start) == 1)
		return (redirect_error_print(fn_start), -1);
	if (owned_token->type == T_REDIRECT_STDOUT)
		fd = open(fn_start, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else
		fd = open(fn_start, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd < 0)
		return (vector_free(vec_fds, close_fd), perror(fn_start), fd);
	if (vector_append(vec_fds, &fd))
		return (vector_free(vec_fds, close_fd), 1);
	return (dup_to_lget(vec_fds, fd));
}

static int	redir_stdin_token_found(const char *filename)
{
	int		open_fd;

	open_fd = open(filename, O_RDONLY);
	if (open_fd < 0)
		return (msh_error(filename), 1);
	dup2(open_fd, 0);
	close(open_fd);
	return (0);
}

int	cleanup_pipes(t_pipe_info *pipeinfo)
{
	if (pipeinfo->pipefd[0])
		close (pipeinfo->pipefd[0]);
	if (pipeinfo->pipefd[1])
		close (pipeinfo->pipefd[1]);
	if (pipeinfo->old_pipe != -1)
		close (pipeinfo->old_pipe);
	return (0);
}

/*	
**	need size rather than just looking for T_END because you can have multiple
**	commands in a vector of t_owned_tokens.
**/

int	open_redirects(t_vector *tokens, int start, int stop, t_vector *vec_fds)
{
	int				i;
	int				ret;
	t_owned_token	*current;

	i = start;
	ret = 0;
	while (i < stop)
	{
		current = (t_owned_token *)tokens->data + i++;
		if (is_redirect_type(current->type) && current->type != T_HEREDOC)
		{
			if (current->type == T_REDIRECT_STDIN)
			{
				if (is_directory(current[1].str))
					return (redirect_error_print(current[1].str), 1);
				ret = redir_stdin_token_found(current[1].str);
			}
			else
				ret = redir_stdout_token_found(current, vec_fds,
						(current + 1)->str);
			if (ret)
				return (ret);
		}
	}
	return (0);
}
