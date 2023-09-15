/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:00:30 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/15 13:49:43 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include "libft.h"

/*
**	print_here_doc_contents
**	mostly for debugging purposes...
**	Will actually need to fork and dup after fork.

	// dup2(heredoc_fd, 0);
	// read(0, buf, 100);

*/

int	print_here_doc_contents(int heredoc_fd)
{
	char	buf[100];

	ft_bzero(buf, 100);
	read(heredoc_fd, buf, 100);
	write(1, buf, 100);
	write(1, "\n", 1);
	close(heredoc_fd);
	return (0);
}
