/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 07:51:09 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/21 14:58:37 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	get_command_segment
**	
*/

int	get_command_segment(t_vector *tokens, int i, int size)
{
	t_owned_token	*current;

	while (i < size)
	{
		i++;
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

bool	load_pipe_vec(t_vector *pipes, t_vector *tokens)
{
	t_owned_token	*current;
	size_t				i;
	int					j;

	i = 0;
	j = 0;
	while (i < tokens->size)
	{
		current = (t_owned_token *)tokens->data + i;
		if (current->type == T_PIPE)
		{
			if (vector_append(pipes, &j))
				return (vector_clear(pipes), 1);
			j = -1;
		}
		i++;
		j++;
	}
	return (0);
}

/*
**	my_vector_pop_n
**	
*/

t_vector	*my_vector_pop_n(t_vector *vector, size_t index, size_t n)
{
	ft_memmove(vector->data + index * vector->elem_size,
		vector->data + index + n,
		(vector->size - index - n) * vector->elem_size);
	vector->size -= n;
	return (vector);
}

/*
**	pipe_loop
**	
*/

int	pipe_loop(t_vector *tokens, int size)
{
	t_vector		pipes;
	int				piping;
	int				ret;

	ret = 0;
	piping = 0;
	vector_init(&pipes, sizeof(int));
	load_pipe_vec(&pipes, tokens);
	while (pipes.size > 0)
	{
		piping = 1;
		ft_printf("This should only print if theres a pipe!\n");
		// create pipe and fork here?
		ret = single_command(tokens, *(int *)pipes.data);
		my_vector_pop_n(&pipes, 0, 1);
	}
	if (!piping)
	{
		ft_printf("This should only print if there is no pipe\n");
		ret = single_command(tokens, size);
	}
	return (vector_clear(&pipes), ret);
}
