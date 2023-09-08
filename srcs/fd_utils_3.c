/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:54:41 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/08 14:59:59 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filedescriptors.h"
#include <unistd.h>

int	cleanup_pipes(t_pipe_info *pipeinfo)
{
	(void) pipeinfo;
	if (pipeinfo->pipefd[0])
		close (pipeinfo->pipefd[0]);
	if (pipeinfo->pipefd[1])
		close (pipeinfo->pipefd[1]);
	return (0);
}
