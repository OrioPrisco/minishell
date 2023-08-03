/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 09:08:51 by dpentlan          #+#    #+#             */
/*   Updated: 2023/08/03 19:21:21 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "tokens.h"
#include "filedescriptors.h"
#include "minishell.h"
#include "ft_printf.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static bool	check_for_redirects(t_vector *tokens, int start, int stop)
{
	int				i;
	t_owned_token	*current;

	i = start;
	while (i < stop)
	{
		current = (t_owned_token *)tokens->data + i;
		if (current->type == T_REDIRECT_STDOUT
			|| current->type == T_REDIRECT_STDOUT_APPEND)
			return (1);
		i++;
	}
	return (0);
}

/*
**	check_and_open_redirects
**	
*/

int	check_and_open_redirects(t_vector *tokens, t_vector *vec_fds,
							int start, int stop)
{
	int			ret;

	ret = 0;
	if (check_for_redirects(tokens, start, stop))
	{
		ret = open_redirects(tokens, start, stop, vec_fds);
		if (ret)
			return (close_open_redirects(vec_fds), ret);
	}
	return (0);
}

/*
**	func_name
**	
*/

void	cleanup_redirects(t_vector *vec_fds)
{
	close_open_redirects(vec_fds);
	vector_clear(vec_fds);
}

/*	
**	tokens is pointer to token space
**	return could be return status of command?
**	print_relavent_tokens(tokens, start, stop);
**	print_open_redirects((t_fds *)vec_fds.data, vec_fds.size);
**	RETURN
**		Returns 0 on success and return int from called functions on error.

**	This functions will only be called from a child process. So rather than
		return, we should exit.
**/

int	single_command(t_vector *tokens, int start, int stop, t_cominfo *cominfo)
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
		return (-1);
	if (here_doc_contents)
		print_here_doc_contents(here_doc_contents);
	ret = check_and_open_redirects(tokens, &vec_fds, start, stop);
	if (ret)
		return (ret);
	execve_command = access_loop((t_owned_token *)tokens->data + start,
			cominfo->envp);
	if (!execve_command)
		return (perror("malloc"), -1);
	print_access_debug(execve_command);
	execve_com_args = construct_execve_args((t_com_segment){tokens, start, stop},
		execve_com_args);
	if (!execve_com_args)
		return (1);
	print_execve_args(execve_com_args);
	execve(execve_command, execve_com_args, cominfo->envp);
	cleanup_redirects(&vec_fds);
	free(execve_command);
	return (0);
}

/*	
**	recursive function for crawling the abstract syntax tree.
**	
**	WORK IN PROGRESS. Initial version of this function is just for testing
**	interface with fd handler functions
**	this should call single command with token address of where to start
**	and the number of tokens to look through (adjust based on presence of 
**	&& || or T_END)
**/

int	tree_crawler(t_vector *tokens, t_cominfo *cominfo)
{
	t_vector	pids;

	vector_init(&pids, sizeof(int));
	fork_loop(tokens, cominfo, &pids);
	msh_wait(&pids);
	vector_clear(&pids);
	return (0);
}
