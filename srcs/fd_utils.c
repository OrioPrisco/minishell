/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:21:36 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/07 17:37:25 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_fn_from_tokens(const char *fn)
{
	char	*fn_trimmed;
	int		i;

	i = 0;
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

int	open_redir_stdout(t_fds *fds, const char *fn)
{
	char	*fn_trimmed;

	fn_trimmed = get_fn_from_tokens(fn);
	if (!fn_trimmed)
		return (1);
	fds->fn = fn_trimmed;
	fds->fd = open(fn_trimmed, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fds->fd < 0)
		return (1);
	return (0);
}

int	open_redir_stdout_append(t_fds *fds, const char *fn)
{
	char	*fn_trimmed;

	fn_trimmed = get_fn_from_tokens(fn);
	if (!fn_trimmed)
		return (1);
	fds->fn = fn_trimmed;
	fds->fd = open(fn_trimmed, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fds->fd < 0)
		return (1);
	return (0);
}

bool	redir_token_found(t_fds *current, char *fn_start, t_vector *vec_fds,
					t_token *tokens)
{
	int	(*redir)(t_fds *, const char *);
	int	ret;

	ret = 0;
	if (tokens->type == T_REDIRECT_STDOUT)
		redir = &open_redir_stdout;
	if (tokens->type == T_REDIRECT_STDOUT_APPEND)
		redir = &open_redir_stdout_append;
	ret = (*redir)(current, fn_start);
	if (!ret)
	{
		if (vector_append(vec_fds, current))
			return (vector_clear(vec_fds), 1);
	}
	else
		return (vector_clear(vec_fds), ret);
	dup_to_lgett(vec_fds, current);
	return (0);
}

/*	
**	NOTE: What if the last token is a space? 
**	
**/

int	open_redirects(t_token *tokens, int size, t_vector *vec_fds)
{
	t_fds		current;
	int			i;

	i = 0;
	while (i < size)
	{
		ft_bzero(&current, sizeof(t_fds));
		if ((tokens[i].type == T_REDIRECT_STDOUT
				|| tokens[i].type == T_REDIRECT_STDOUT_APPEND)
			&& i == size)
			return (2);
		if (tokens[i].type == T_REDIRECT_STDOUT
			|| tokens[i].type == T_REDIRECT_STDOUT_APPEND)
		{
			if (redir_token_found(&current, (char *)tokens[i + 2].strview.start,
					vec_fds, &tokens[i]))
				return (1);
		}
		i++;
	}
	return (0);
}
