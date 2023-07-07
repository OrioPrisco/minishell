/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:21:36 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/07 14:16:04 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redir_stdout(t_fds *fds, const char *fn)
{
	char	*trimmed_fn;
	int		i;
	if (fds) {}

	i = 0;
	trimmed_fn = ft_strdup(fn);
	if (!trimmed_fn)
		return (1);
	while (trimmed_fn[i])
	{
		if (trimmed_fn[i] == ' ') 
		{
			trimmed_fn[i] = 0;
			break ;
		}
		i++;
	}
	ft_printf("redirecting overwrite to %s\n", trimmed_fn);
	free(trimmed_fn);
	return (0);
}

int	open_redir_stdout_append(t_fds *fds, const char *fn)
{
	char	*trimmed_fn;
	int		i;
	if (fds) {}

	i = 0;
	trimmed_fn = ft_strdup(fn);
	if (!trimmed_fn)
		return (1);
	while (trimmed_fn[i])
	{
		if (trimmed_fn[i] == ' ') 
		{
			trimmed_fn[i] = 0;
			break ;
		}
		i++;
	}
	ft_printf("redirecting append to %s\n", trimmed_fn);
	free(trimmed_fn);
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
			if (!open_redir_stdout(&current, (char *)tokens[i + 2].strview.start))
			{
				if (vector_append(vec_fds, &current))
					return (vector_clear(vec_fds), NULL);
			}
			else
				return (vector_clear(vec_fds), NULL);
		}
		if (tokens[i].type == T_REDIRECT_STDOUT_APPEND)
		{
			if (!open_redir_stdout_append(&current, (char *)tokens[i + 2].strview.start))
			{
				if (vector_append(vec_fds, &current))
					return (vector_clear(vec_fds), NULL);
			}
			else
				return (vector_clear(vec_fds), NULL);
		}
		i++;
	}
	return (vec_fds->data);
}
