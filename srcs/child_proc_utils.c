/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:57:40 by dpentlan          #+#    #+#             */
/*   Updated: 2023/08/31 18:08:25 by dpentlan         ###   ########.fr       */
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
**/

void	single_command(t_vector *tokens, int start, int stop,
					t_cominfo *cominfo)
{
	t_vector	vec_fds;
	int			ret;
	char		*execve_command;
	char		**execve_com_args;

	execve_command = 0;
	execve_com_args = 0;
	vector_init(&vec_fds, sizeof(t_fds));
	ret = check_and_open_redirects(tokens, &vec_fds, start, stop);
	if (ret)
		msh_exit_child(cominfo->com_list);
	redir_stdout_and_clean(&vec_fds);
	execve_command = find_executable(cominfo,
			(t_com_segment){tokens, start, stop});
	if (!execve_command)
	{
		cleanup_redirects(&vec_fds);
		msh_exit_child(cominfo->com_list);
	}
	execve_com_args = construct_execve_args(
			(t_com_segment){tokens, start, stop}, execve_com_args);
	if (!execve_com_args)
		msh_error("malloc");
	execve(execve_command, execve_com_args, cominfo->envp);
	msh_exit_child(cominfo->com_list);
}
