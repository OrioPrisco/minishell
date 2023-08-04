/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:44:53 by dpentlan          #+#    #+#             */
/*   Updated: 2023/08/04 17:04:35 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "vector.h"
#include "child.h"
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
		single_command(tokens, 0, size, cominfo);
	return (0);
}

/*
**	multi_fork
		used when pipes are present and multiple forks need to occur.
**	pipe_loop(tokens, cominfo, &pipes);
**
*/

int	multi_fork(t_vector *tokens, t_cominfo *cominfo, t_vector *pids)
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
		single_command(tokens, 0, size, cominfo);
	return (0);
}
