/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:57:40 by dpentlan          #+#    #+#             */
/*   Updated: 2023/10/04 18:35:06 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "child.h"
#include "redirects.h"
#include <unistd.h>
#include "tokens.h"
#include "error.h"
#include "utils.h"

static int	pipe_dups(t_com_segment *com_seg, t_pipe_info *pipeinfo)
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

void	open_heredocs(t_owned_token *tok, size_t start, size_t stop)
{
	size_t	i;

	i = start;
	while (i < stop)
	{
		if (tok[i].type == T_HEREDOC)
		{
			close(STDIN_FILENO);
			dup2(tok[i].hd, STDIN_FILENO);
			close(tok[i].hd);
			tok[i].hd = 0;
		}
		i++;
	}
}

/*	
**	tokens is pointer to token space
**	return could be return status of command?
**	print_relavent_tokens(tokens, start, stop);
**	print_open_redirects((t_fds *)vec_fds.data, vec_fds.size);

**	RETURN
**		Function does not return, child process should terminate here in some way.
**/
void	single_command(t_com_segment com_seg, t_cominfo *cominfo,
			t_pipe_info *pipeinfo)
{
	t_vector	vec_fds;
	int			ret;

	vector_init(&vec_fds, sizeof(int));
	if (pipeinfo->pipefd[0] != 0 && pipeinfo->pipefd[1] != 0)
		pipe_dups(&com_seg, pipeinfo);
	ret = check_and_open_redirects(com_seg.tokens, &vec_fds, com_seg.start,
			com_seg.stop);
	if (ret)
	{
		cleanup_pipes(pipeinfo);
		msh_exit(cominfo, 1, 0);
	}
	open_heredocs(com_seg.tokens->data, com_seg.start, com_seg.stop);
	if (vec_fds.size > 0)
		dup2(((int *)vec_fds.data)[vec_fds.size - 1], 1);
	vector_free(&vec_fds, close_fd);
	cleanup_pipes(pipeinfo);
	exec_command(cominfo, com_seg);
	msh_exit(cominfo, 0, 0);
}
