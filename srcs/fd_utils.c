/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:21:36 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/07 15:28:23 by dpentlan         ###   ########.fr       */
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

	if (fds)
	{
	}
	fn_trimmed = get_fn_from_tokens(fn);
	if (!fn_trimmed)
		return (1);
	fds->fn = fn_trimmed;
	ft_printf("redirecting overwrite to %s\n", fn_trimmed);
	return (0);
}

int	open_redir_stdout_append(t_fds *fds, const char *fn)
{
	char	*fn_trimmed;

	if (fds)
	{
	}
	fn_trimmed = get_fn_from_tokens(fn);
	if (!fn_trimmed)
		return (1);
	fds->fn = fn_trimmed;
	ft_printf("redirecting append to %s\n", fn_trimmed);
	return (0);
}

bool	redir_token_found(t_fds *current, char *fn_start, t_vector *vec_fds,
					int (*redir)(t_fds *, const char *))
{
	if (!(*redir)(current, fn_start))
	{
		if (vector_append(vec_fds, current))
			return (vector_clear(vec_fds), 1);
	}
	else
		return (vector_clear(vec_fds), 1);
	return (0);
}

t_fds	*open_redirects(t_token *tokens, int size, t_vector *vec_fds)
{
	t_fds		current;
	int			i;

	i = 0;
	while (i < size)
	{
		ft_bzero(&current, sizeof(t_fds));
		if (tokens[i].type == T_REDIRECT_STDOUT)
		{
			if (redir_token_found(&current, (char *)tokens[i + 2].strview.start,
					vec_fds, &open_redir_stdout))
				return (0);
		}
		if (tokens[i].type == T_REDIRECT_STDOUT_APPEND)
		{
			if (redir_token_found(&current, (char *)tokens[i + 2].strview.start,
					vec_fds, &open_redir_stdout_append))
				return (0);
		}
		i++;
	}
	return (vec_fds->data);
}
