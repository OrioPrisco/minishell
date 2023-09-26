/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:21:36 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/26 15:35:10 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filedescriptors.h"
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

static int	redir_stdout_token_found(t_owned_token *owned_token,
							t_vector *vec_fds, char *fn_start)
{
	int		fd;

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
		current = (t_owned_token *)tokens->data + i;
		if (is_redirect_type(current->type) && current->type != T_HEREDOC)
		{
			if (is_directory(current[1].str))
				return (redirect_error_print(current[1].str), 1);
			if (current->type == T_REDIRECT_STDIN)
				ret = redir_stdin_token_found(current[1].str);
			else
				ret = redir_stdout_token_found(current, vec_fds,
						(current + 1)->str);
			if (ret)
				return (ret);
		}
		i++;
	}
	return (0);
}
