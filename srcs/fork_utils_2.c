/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:44:53 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/05 10:31:11 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "vector.h"
#include "child.h"
#include "ft_printf.h"
#include <unistd.h>
#include "libft.h"

int	single_fork(t_vector *tokens, t_cominfo *cominfo, t_vector *pids,
		t_pipe_info *pipeinfo)
{
	int				pid;
	int				size;

	size = 0;
	while (((t_owned_token *)tokens->data + size)->type != T_END)
		size++;
	pid = fork();
	if (pid < 0)
		return (-1);
	if (vector_append(pids, (int *)&pid))
		return (-1);
	if (pid == 0)
		single_command((t_com_segment){tokens, 0, size, size}, cominfo,
			pipeinfo);
	return (0);
}

/*
	NAME
		pipe_setup
	DESCRIPTION
		
	RETURN
		
*/

int	pipe_setup(t_vector *tokens, t_cominfo *cominfo, t_vector *pids,
		t_pipe_info *pipeinfo)
{
	int				size;
	int				i;
	int				j;

	i = -1;
	j = 0;
	size = 0;
	while (((t_owned_token *)tokens->data + size)->type != T_END)
		size++;
	while (++i < size)
	{
		if (((t_owned_token *)tokens->data + i)->type == T_PIPE)
		{
			if (pipe(pipeinfo->pipefd))
				return (-1);
			multi_fork((t_com_segment){tokens, j, i, size}, cominfo,
				pids, pipeinfo);
			j = i + 1;
		}
	}
	multi_fork((t_com_segment){tokens, j, i, size}, cominfo, pids, pipeinfo);
	return (0);
}

/*
**	multi_fork
		used when pipes are present and multiple forks need to occur.
**	pipe_loop(tokens, cominfo, &pipes);
**
*/

int	multi_fork(t_com_segment com_seg, t_cominfo *cominfo, t_vector *pids,
				t_pipe_info *pipeinfo)
{
	int		pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (vector_append(pids, (int *)&pid))
		return (-1);
	if (pid == 0)
		single_command(com_seg, cominfo, pipeinfo);
	else
	{
		close(pipeinfo->pipefd[1]);
		if (pipeinfo->old_pipe != -1)
			close(pipeinfo->old_pipe);
		pipeinfo->old_pipe = pipeinfo->pipefd[0];
	}
	return (0);
}
