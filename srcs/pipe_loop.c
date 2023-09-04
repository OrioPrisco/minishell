/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 07:51:09 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/04 16:15:28 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include "vector.h"
#include "libft.h"
#include "child.h"

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

/*
**	pipe_loop
**	
			ft_printf("Pipe detected! Multiple commands:\n");
**	
		ft_printf("No pipe detected. Single command:\n");
**	
**	I think this 
*/
/*
int	pipe_loop(t_vector *tokens, t_cominfo *cominfo, t_vector *pipes)
{
	int				*pos;

	while (pipes->size > 1)
	{
		pos = (int *)pipes->data;
		single_command((t_com_segment){tokens, *pos + 1, *(pos + 1)}, cominfo);
		vector_pop_n(pipes, 0, 1);
	}
	return (0);
}
*/
/*
**	fork_loop
**	Errors not handled yet. think about return in case of fork failure or malloc
		failure.
	
	Consider adding fourth argument as pointer to int to return the return of
		executed process.
*/

int	fork_loop(t_vector *tokens, t_cominfo *cominfo, t_vector *pids)
{
	t_vector		pipes;
	int				ret;

	ret = 0;
	vector_init(&pipes, sizeof(int));
	ret = load_pipe_vec(&pipes, tokens);
	if (ret < 0)
		return (vector_clear(&pipes), -1);
	else if (ret > 0)
	{
		if (pipe_setup(tokens, cominfo, pids))
			return (-1);
	}
	else
	{
		if (single_fork(tokens, cominfo, pids))
			return (-1);
	}
	return (vector_clear(&pipes), ret);
}
