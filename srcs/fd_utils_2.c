/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:27:39 by dpentlan          #+#    #+#             */
/*   Updated: 2023/08/10 13:57:06 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "filedescriptors.h"
#include "ft_printf.h"
#include "libft.h"
#include "tokens.h"
#include "vector.h"
#include <fcntl.h>
#include <unistd.h>

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

/*	
**	NOTE: since the the fds.fn is a pointer, these need to be freed here.
**	This loop only frees 
**	
**	after close(fds[i].fd);
**	ft_printf("closed fd: %d, fn %s, fd_cloexec %d\n",
		fds[i].fd, fds[i].fn, fds[i].fd_cloexec);
**	before free(fds[i].fn);
*/

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
				vector_pop(vec_fds, i,
					&(((t_fds *)vec_fds->data)[vec_fds->size]));
			}
			i--;
		}
	}
	if (vec_fds->size <= 0)
		vector_free(vec_fds, free_fds);
	return (0);
}

/*	
**	dup2 to least greater than or equal to 10
**	
**/

int	dup_to_lget(t_vector *vec_fds, t_fds *current)
{
	size_t	i;
	int		greatest;
	int		ret;

	i = 0;
	ret = 0;
	greatest = 10;
	while (i < vec_fds->size)
	{
		if (((t_fds *)vec_fds->data)[i].fd >= greatest)
			greatest = ((t_fds *)vec_fds->data)[i].fd + 1;
		i++;
	}
	ret = dup2(current->fd, greatest);
	if (ret < 0)
		return (ret);
	close(current->fd);
	((t_fds *)vec_fds->data)[vec_fds->size - 1].fd = greatest;
	return (0);
}

int	redir_stdin_token_found(char *filename)
{
	int	open_fd;

	open_fd = open(filename, O_RDONLY);
	if (open_fd < 0)
		msh_error(filename);
	dup2(open_fd, 0);
	close(open_fd);
	return (0);
}

/*
	NAME
		final_dup_redir_stdout
	DESCRIPTION
		
	RETURN
		
*/

bool	final_dup_redir_stdout(t_vector *vec_fds)
{
	int	last;

	last = 1;
	if (vec_fds->size > 0)
	{
		last = ((t_fds *)vec_fds->data + vec_fds->size - 1)->fd;
		ft_printf("last fd: %d\n", last);
		dup2(last, 1);
	}
	return (0);
}
