/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:27:39 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/26 14:52:41 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filedescriptors.h"
#include "ft_printf.h"
#include "vector.h"
#include <fcntl.h>
#include <unistd.h>
#include "error.h"
#include "minishell.h"

/*	
**	dup2 to least greater than or equal to 10
**	
**/

int	dup_to_lget(t_vector *vec_fds, int fd)
{
	size_t	i;
	int		greatest;
	int		ret;

	i = 0;
	ret = 0;
	greatest = 10;
	while (i < vec_fds->size)
	{
		if (((int *)vec_fds->data)[i] >= greatest)
			greatest = ((int *)vec_fds->data)[i] + 1;
		i++;
	}
	ret = dup2(fd, greatest);
	close(fd);
	if (ret < 0)
		return (ret);
	((int *)vec_fds->data)[vec_fds->size - 1] = greatest;
	return (0);
}

int	redir_stdin_token_found(const char *filename)
{
	int		open_fd;

	open_fd = open(filename, O_RDONLY);
	if (open_fd < 0)
		msh_error(filename);
	dup2(open_fd, 0);
	close(open_fd);
	return (0);
}
