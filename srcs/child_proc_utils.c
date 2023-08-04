/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:57:40 by dpentlan          #+#    #+#             */
/*   Updated: 2023/08/04 17:04:58 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "child.h"
#include "minishell.h"
#include "vector.h"
#include "filedescriptors.h"
#include <stdlib.h>
#include <unistd.h>

/*	
**	tokens is pointer to token space
**	return could be return status of command?
**	print_relavent_tokens(tokens, start, stop);
**	print_open_redirects((t_fds *)vec_fds.data, vec_fds.size);

**	RETURN
**		Function does not return, child process should terminate here in some way.
**/

void	single_command(t_vector *tokens, int start, int stop,
					t_cominfo *cominfo)
{
	t_vector	vec_fds;
	int			ret;
	int			here_doc_contents;
	char		*execve_command;
	char		**execve_com_args;

	ret = 0;
	execve_command = 0;
	execve_com_args = 0;
	vector_init(&vec_fds, sizeof(t_fds));
	here_doc_contents = check_and_open_heredoc(tokens, start, stop, cominfo);
	if (here_doc_contents < 0)
		msh_exit(cominfo->envp, cominfo->com_list);
	if (here_doc_contents)
		print_here_doc_contents(here_doc_contents);
	ret = check_and_open_redirects(tokens, &vec_fds, start, stop);
	if (ret)
		msh_exit(cominfo->envp, cominfo->com_list);
	execve_command = access_loop((t_owned_token *)tokens->data + start,
			cominfo->envp);
	if (!execve_command)
		msh_exit(cominfo->envp, cominfo->com_list);
	print_access_debug(execve_command);
	execve_com_args = construct_execve_args(
			(t_com_segment){tokens, start, stop}, execve_com_args);
	if (!execve_com_args)
		msh_exit(cominfo->envp, cominfo->com_list);
	print_execve_args(execve_com_args);
	if (execve_command[0])
		execve(execve_command, execve_com_args, cominfo->envp);
	cleanup_redirects(&vec_fds);
	free(execve_command);
	msh_exit(cominfo->envp, cominfo->com_list);
}
