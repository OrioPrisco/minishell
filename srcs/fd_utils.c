/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:21:36 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/08 14:04:44 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_fn_from_tokens(const char *fn)
{
	char	*fn_trimmed;
	int		i;

	i = 0;
	fn_trimmed = 0;
	fn_trimmed = ft_strdup(fn);
	if (!fn_trimmed)
		return (0);
	while (fn_trimmed[i])
	{
		if (fn_trimmed[i] == ' ')
		{
			fn_trimmed[i] = 0;
			break ;
		}
		i++;
	}
	return (fn_trimmed);
}

/*	
**	in the future my hope is not need the get_fn_from_tokens function, but
**	i need it now to get a null terminated string for the file name.
**	
**/

int	open_trunc(t_fds *fds, const char *fn, int flags)
{
	char	*fn_trimmed;

	fn_trimmed = 0;
	fn_trimmed = get_fn_from_tokens(fn);
	if (!fn_trimmed)
		return (1);
	fds->fn = fn_trimmed;
	fds->fd = open(fn_trimmed, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fds->fd < 0)
		return (1);
	if (flags == 1)
		fds->fd_cloexec = 1;
	return (0);
}

int	open_append(t_fds *fds, const char *fn, int flags)
{
	char	*fn_trimmed;

	fn_trimmed = 0;
	fn_trimmed = get_fn_from_tokens(fn);
	if (!fn_trimmed)
		return (1);
	fds->fn = fn_trimmed;
	fds->fd = open(fn_trimmed, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fds->fd < 0)
		return (1);
	if (flags == 1)
		fds->fd_cloexec = 1;
	return (0);
}

static int	redir_token_found(t_token *tokens, t_vector *vec_fds, char *fn_start)
{
	int		(*redir)(t_fds *, const char *, int);
	int		ret;
	t_fds	current;

	ret = 0;
	ft_bzero(&current, sizeof(t_fds));
	if (tokens->type == T_REDIRECT_STDOUT)
		redir = &open_trunc;
	if (tokens->type == T_REDIRECT_STDOUT_APPEND)
		redir = &open_append;
	ret = (*redir)(&current, fn_start, 1);
	if (!ret)
	{
		if (vector_append(vec_fds, &current))
			return (vector_clear(vec_fds), 1);
	}
	else
		return (vector_clear(vec_fds), ret);
	dup_to_lget(vec_fds, &current);
	return (0);
}

/*	
**	need syntax checking prior to calling open_redirects.
**	for this reason, the first if that checks size may not be necessary
**	but only after proper syntax checking is done.
**/

int	open_redirects(t_token *tokens, int size, t_vector *vec_fds)
{
	int			i;
	int			ret;

	i = 0;
	ret = 0;
	while (i < size)
	{
		if ((tokens[i].type == T_REDIRECT_STDOUT
				|| tokens[i].type == T_REDIRECT_STDOUT_APPEND)
			&& (i == size - 1 || i == size - 2))
			return (2);
		else if (tokens[i].type == T_REDIRECT_STDOUT
			|| tokens[i].type == T_REDIRECT_STDOUT_APPEND)
		{
			ret = redir_token_found(&tokens[i], vec_fds,
						   (char *)tokens[i + 2].strview.start);
			if (ret)
				return (ret);
		}
		i++;
	}
	return (0);
}
