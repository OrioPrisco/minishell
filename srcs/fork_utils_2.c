/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:44:53 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/04 13:01:12 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "vector.h"
#include "child.h"
#include "ft_printf.h"
#include <unistd.h>

int	single_fork(t_vector *tokens, t_cominfo *cominfo, t_vector *pids)
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
		single_command((t_com_segment){tokens, 0, size}, cominfo);
	return (0);
}

/*
	NAME
		pipe_setup
	DESCRIPTION
		
	RETURN
		
*/

int	pipe_setup(t_vector *tokens, t_cominfo *cominfo, t_vector *pids)
{
	int				size;
	int				i;
	int				j;
	int				pipefd[2];

	i = 0;
	j = 0;
	size = 0;
	if (pipe(pipefd))
		return (-1);
	while (((t_owned_token *)tokens->data + size)->type != T_END)
		size++;
	while (i < size)
	{
		if (((t_owned_token *)tokens->data + i)->type == T_PIPE)
		{
			ft_printf("Passing command from %d to %d\n", j, i - 1);
			multi_fork((t_com_segment){tokens, j, i}, cominfo, pids);
			j = i + 1;
		}
		i++;
	}
	if (((t_owned_token *)tokens->data + i)->type == T_END)
		ft_printf("Passing command from %d to %d\n", j, i);
			multi_fork((t_com_segment){tokens, j, i}, cominfo, pids);
	return (0);
}

/*
**	multi_fork
		used when pipes are present and multiple forks need to occur.
**	pipe_loop(tokens, cominfo, &pipes);
**
*/

int	multi_fork(t_com_segment com_seg, t_cominfo *cominfo, t_vector *pids)
{
	int		pid;
	int		size;

	size = 0;
	while (((t_owned_token *)com_seg.tokens->data + size)->type != T_END)
		size++;
	pid = fork();
	if (pid < 0)
		return (-1);
	if (vector_append(pids, (int *)&pid))
		return (-1);
	if (pid == 0)
		single_command(com_seg, cominfo);
	return (0);
}
