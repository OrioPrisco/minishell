/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:27:39 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/07 15:28:11 by dpentlan         ###   ########.fr       */
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
