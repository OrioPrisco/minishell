/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:27:39 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/07 17:37:21 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirects_fn(t_fds *fds, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(fds[i].fn);
		i++;
	}
}

void	free_redirects_all(t_fds *fds, int size)
{
	if (fds)
	{
		free_redirects_fn(fds, size);
		free(fds);
	}
}

/*	
**	mostly for debugging to view fds vector data
**	
**/

void	print_open_redirects(t_fds *fds, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_printf("#%d: fd: %d, fn: %s\n", (i + 1), fds[i].fd, fds[i].fn);
		i++;
	}
}

int	close_open_redirects(t_fds *fds, int size)
{
	while (size)
	{
		ft_printf("closing fd: %d fd: %s\n", fds[size - 1].fd, fds[size - 1].fn);
		close(fds[size - 1].fd);
		size--;
	}
	return (0);
}

/*	
**	dup2 to least greater than or equal to 10
**	
**/

int	dup_to_lgett(t_vector *vec_fds, t_fds *current)
{
	size_t	i;
	int		greatest;

	i = 0;
	greatest = 10;
	while (i < vec_fds->size)
	{
		if (((t_fds *)vec_fds->data)[i].fd >= greatest)
			greatest = ((t_fds *)vec_fds->data)[i].fd + 1;
		i++;
	}
	dup2(current->fd, greatest);
	close(current->fd);
	((t_fds *)vec_fds->data)[vec_fds->size - 1].fd = greatest;
	return (0);
}
