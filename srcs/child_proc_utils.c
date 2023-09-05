/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:57:40 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/05 10:24:41 by dpentlan         ###   ########.fr       */
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

void	msh_exit_child(t_vector *com_list)
{
	vector_free(com_list, free_str);
	exit(EXIT_SUCCESS);
}

/*
	NAME
		pipe_dups
	DESCRIPTION
		
	RETURN
		
*/

int	pipe_dups(t_com_segment *com_seg, t_pipe_info *pipeinfo)
{
	if (com_seg->stop != com_seg->size)
	{
		dup2(pipeinfo->old_pipe, STDIN_FILENO);
		dup2(pipeinfo->pipefd[1], STDOUT_FILENO);
	}
	if (com_seg->stop == com_seg->size)
	{
		dup2(pipeinfo->old_pipe, STDIN_FILENO);
	}
	return (0);
}

/*	
**	tokens is pointer to token space
**	return could be return status of command?
**	print_relavent_tokens(tokens, start, stop);
**	print_open_redirects((t_fds *)vec_fds.data, vec_fds.size);

**	RETURN
**		Function does not return, child process should terminate here in some way.

	These lines were removed after vector init. The heredoc stuff should be moved
		to parsing. Keeping here for the moment for reference.

	int			here_doc_contents;
	
	here_doc_contents = check_and_open_heredoc(tokens, start, stop, cominfo);
	if (here_doc_contents < 0)
		msh_exit_child(cominfo->envp, cominfo->com_list);
	if (here_doc_contents)
		print_here_doc_contents(here_doc_contents);
	//print_open_redirects((t_fds *)vec_fds.data, vec_fds.size);
	//table_print(execve_com_args);
	//ft_printf("pipeinfo: %d %d %d\n", pipeinfo->pipefd[0], pipeinfo->pipefd[1], pipeinfo->old_pipe);
**/

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
		msh_exit_child(cominfo->com_list);
	redir_stdout_and_clean(&vec_fds);
	exec_command(cominfo, com_seg, &vec_fds);
	msh_exit_child(cominfo->com_list);
}
