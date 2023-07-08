/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:27:39 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/08 12:45:13 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	
**	mostly for debugging to view fds vector data
**	
**/

void	print_open_redirects(t_fds *fds, int size)
{
	int	i;

	i = 0;
	if (size == 0 || fds == NULL)
	{
		ft_printf("No open fds.\n");
		return ;
	}
	while (i < size)
	{
		if (fds[i].fn)
		{
			ft_printf("#%d: fd: %d, fn: %s, fd_cloexec: %d\n",
				(i + 1), fds[i].fd, fds[i].fn, fds[i].fd_cloexec);
		}
		i++;
	}
}

void	my_vector_pop(t_vector *vector, size_t index, void *dest)
{
	ft_memcpy(dest, vector->data + index * vector->elem_size,
		vector->elem_size);
	ft_memmove(vector->data + index * vector->elem_size,
		vector->data + (index + 1) * vector->elem_size,
		(vector->size - index) * vector->elem_size);
	vector->size--;
}

/*	
**	NOTE!!! This function manually closes fds and frees strings etc.
**	This should use vector clear and vector pop conditionally based on if
**	the fd_cloexec flag is on or not.
**	
**/

int	close_open_redirects(t_vector *vec_fds)
{
	t_fds	*fds;
	int		i;

	if (!vec_fds || !vec_fds->data)
		return (0);
	i = vec_fds->size - 1;
	fds = (t_fds *)vec_fds->data;
	if (fds)
	{
		while (i >= 0)
		{
			if (fds[i].fd_cloexec)
			{
				close(fds[i].fd);
				free(fds[i].fn);
				my_vector_pop(vec_fds, i,
					&(((t_fds *)vec_fds->data)[vec_fds->size]));
			}
			i--;
		}
	}
	if (vec_fds->size <= 0)
		vector_clear(vec_fds);
	return (0);
}

/*	
**	dup2 to least greater than or equal to 10
**	
**/

void	dup_to_lget(t_vector *vec_fds, t_fds *current)
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
}
