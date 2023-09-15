/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:57:40 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/15 16:08:01 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "child.h"
#include "minishell.h"
#include "vector.h"
#include "filedescriptors.h"
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"
#include "ft_printf.h"
#include "tokens.h"
#include "env_var.h"

void	msh_exit_child(t_vector *com_list, int ret)
{
	vector_free(com_list, free_str);
	if (ret)
		exit(ret);
	else
		exit(EXIT_SUCCESS);
}

int	pipe_dups(t_com_segment *com_seg, t_pipe_info *pipeinfo)
{
	if (com_seg->stop == com_seg->size)
		dup2(pipeinfo->old_pipe, STDIN_FILENO);
	else
	{
		dup2(pipeinfo->old_pipe, STDIN_FILENO);
		dup2(pipeinfo->pipefd[1], STDOUT_FILENO);
	}
	return (0);
}

void	single_command(t_com_segment com_seg, t_cominfo *cominfo,
			t_pipe_info *pipeinfo)
{
	t_vector	vec_fds;
	int			ret;

	vector_init(&vec_fds, sizeof(t_fds));
	if (pipeinfo->pipefd[0] != 0 && pipeinfo->pipefd[1] != 0)
		pipe_dups(&com_seg, pipeinfo);
	ret = check_and_open_redirects(com_seg.tokens, &vec_fds, com_seg.start,
			com_seg.stop);
	if (ret)
		msh_exit_child(cominfo->com_list, ret);
	redir_stdout_and_clean(&vec_fds, pipeinfo);
	exec_command(cominfo, com_seg);
	msh_exit_child(cominfo->com_list, ret);
}
