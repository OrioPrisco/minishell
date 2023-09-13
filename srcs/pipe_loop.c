/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 07:51:09 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/13 12:15:00 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include "vector.h"
#include "libft.h"
#include "child.h"
#include "ft_printf.h"

/*
**	get_command_segment
**	
*/

int	get_command_segment(t_vector *tokens, int i, int size)
{
	t_owned_token	*current;

	while (i < size)
	{
		current = (t_owned_token *)tokens->data + i;
		if (current->type == T_PIPE)
			return (i);
		i++;
	}
	return (i);
}

/*
**	load_pipe_vec
**	
*/

int	load_pipe_vec(t_vector *pipes, t_vector *tokens)
{
	t_owned_token	*current;
	size_t			i;
	int				start;

	start = -1;
	if (vector_append(pipes, (int *)&start))
		return (vector_clear(pipes), -1);
	i = 0;
	while (i < tokens->size)
	{
		current = (t_owned_token *)tokens->data + i;
		if (current->type == T_PIPE)
			if (vector_append(pipes, &i))
				return (vector_clear(pipes), -1);
		i++;
	}
	i--;
	if (vector_append(pipes, (int *)&i))
		return (vector_clear(pipes), -1);
	if (pipes->size > 2)
		return (pipes->size);
	return (0);
}

int	count_pipes(t_vector *tokens)
{
	int				num_pipes;
	int				i;
	t_owned_token	*current;

	num_pipes = 0;
	i = 0;
	while (i < (int)tokens->size)
	{
		current = (t_owned_token *)tokens->data + i;
		if (current->type == T_PIPE)
			num_pipes++;
		i++;
	}
	return (num_pipes);
}

/*
**	fork_loop
**	Errors not handled yet. think about return in case of fork failure or malloc
		failure.
	
	Consider adding fourth argument as pointer to int to return the return of
		executed process.
*/

int	fork_loop(t_vector *tokens, t_cominfo *cominfo, t_vector *pids)
{
	int				num_pipes;
	t_pipe_info		pipeinfo;

	num_pipes = 0;
	ft_bzero((void *)&pipeinfo, sizeof(pipeinfo));
	pipeinfo.old_pipe = -1;
	num_pipes = count_pipes(tokens);
	if (num_pipes == 0)
	{
		if (single_fork(tokens, cominfo, pids, &pipeinfo))
			return (-1);
	}
	else
		if (pipe_setup(tokens, cominfo, pids, &pipeinfo))
			return (-1);
	return (0);
}
