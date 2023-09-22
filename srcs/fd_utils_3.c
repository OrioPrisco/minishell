/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:54:41 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/22 15:24:27 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filedescriptors.h"
#include <unistd.h>
#include "minishell.h"

int	cleanup_pipes(t_pipe_info *pipeinfo)
{
	if (pipeinfo->pipefd[0])
		close (pipeinfo->pipefd[0]);
	if (pipeinfo->pipefd[1])
		close (pipeinfo->pipefd[1]);
	if (pipeinfo->old_pipe != -1)
		close (pipeinfo->old_pipe);
	return (0);
}
