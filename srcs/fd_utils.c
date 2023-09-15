/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:21:36 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/14 14:07:07 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "filedescriptors.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include "tokens.h"
#include "vector.h"

int	open_trunc(t_fds *fds, const char *fn, int flags)
{
	fds->fn = ft_strdup(fn);
	if (!fds->fn)
		return (1);
	fds->fd = open(fn, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fds->fd < 0)
		return (1);
	if (flags == 1)
		fds->fd_cloexec = 1;
	return (0);
}

int	open_append(t_fds *fds, const char *fn, int flags)
{
	fds->fn = ft_strdup(fn);
	if (!fds->fn)
		return (1);
	fds->fd = open(fn, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fds->fd < 0)
		return (1);
	if (flags == 1)
		fds->fd_cloexec = 1;
	return (0);
}

static int	redir_stdout_token_found(t_owned_token *owned_token,
							t_vector *vec_fds, char *fn_start)
{
	int		(*redir)(t_fds *, const char *, int);
	int		ret;
	t_fds	current;

	ret = 0;
	ft_bzero(&current, sizeof(t_fds));
	if (owned_token->type == T_REDIRECT_STDOUT)
		redir = &open_trunc;
	if (owned_token->type == T_REDIRECT_STDOUT_APPEND)
		redir = &open_append;
	ret = (*redir)(&current, fn_start, 1);
	if (!ret)
	{
		if (vector_append(vec_fds, &current))
			return (vector_free(vec_fds, free_fds), 1);
	}
	else
		return (vector_free(vec_fds, free_fds), ret);
	return (dup_to_lget(vec_fds, &current));
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
		if (current->type == T_REDIRECT_STDOUT
			|| current->type == T_REDIRECT_STDOUT_APPEND
			|| current->type == T_REDIRECT_STDIN)
		{
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

void	free_fds(void *to_free)
{
	t_fds	*current;

	current = to_free;
	close(current->fd);
	free(current->fn);
}
