/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:21:36 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/18 15:46:36 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "filedescriptors.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include "tokens.h"
#include "vector.h"

// static char	*get_fn_from_tokens(const char *fn)
// {
// 	char	*fn_trimmed;
// 	int		i;
//
// 	i = 0;
// 	fn_trimmed = 0;
// 	fn_trimmed = ft_strdup(fn);
// 	if (!fn_trimmed)
// 		return (0);
// 	while (fn_trimmed[i])
// 	{
// 		if (fn_trimmed[i] == ' ')
// 		{
// 			fn_trimmed[i] = 0;
// 			break ;
// 		}
// 		i++;
// 	}
// 	return (fn_trimmed);
// }

/*	
**	in the future my hope is not need the get_fn_from_tokens function, but
**	i need it now to get a null terminated string for the file name.
**	
**/

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

static int	redir_token_found(t_owned_token *owned_token,
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
			return (vector_clear(vec_fds), 1);
	}
	else
		return (vector_clear(vec_fds), ret);
	ret = dup_to_lget(vec_fds, &current);
	if (ret)
		return (ret);
	return (0);
}

/*	
**	need syntax checking prior to calling open_redirects.
**	for this reason, the first if that checks size may not be necessary
**	but only after proper syntax checking is done.
**	
**	need size rather than just looking for T_END because you can have multiple
**	commands in a vector of t_owned_tokens.
**/

int	open_redirects(t_vector *tokens, int size, t_vector *vec_fds)
{
	int				i;
	int				ret;
	t_owned_token	*current;

	i = 0;
	ret = 0;
	while (i < size)
	{
		current = (t_owned_token *)tokens->data + i;
		if ((current->type == T_REDIRECT_STDOUT
				|| current->type == T_REDIRECT_STDOUT_APPEND)
			&& i == size - 1)
			return (2);
		else if (current->type == T_REDIRECT_STDOUT
			|| current->type == T_REDIRECT_STDOUT_APPEND)
		{
			ret = redir_token_found(current, vec_fds, (current + 1)->str);
			if (ret)
				return (ret);
		}
		i++;
	}
	return (0);
}
