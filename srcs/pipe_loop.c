/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 07:51:09 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/28 16:16:30 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include "vector.h"
#include "libft.h"

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

int	load_pipe_vec(t_vector *pipes, t_vector *tokens)
{
	t_owned_token	*current;
	size_t			i;
	int				start;

	start = -1;
	if (vector_append(pipes, (int *)&start))
		return (vector_clear(pipes), 1);
	i = 0;
	while (i < tokens->size)
	{
		current = (t_owned_token *)tokens->data + i;
		if (current->type == T_PIPE)
		{
			if (vector_append(pipes, (int *)&i))
				return (vector_clear(pipes), 1);
		}
		i++;
	}
	i--;
	if (vector_append(pipes, (int *)&i))
		return (vector_clear(pipes), 1);
	if (pipes->size > 2)
		return (pipes->size);
	return (0);
}

/*
**	my_vector_pop_n
**	
*/

t_vector	*my_vector_pop_n(t_vector *vector, size_t index, size_t n)
{
	ft_memmove(vector->data + (index * vector->elem_size),
		vector->data + (index * vector->elem_size) + (n * vector->elem_size),
		(vector->size - index - n) * vector->elem_size);
	vector->size -= n;
	return (vector);
}

/*
**	pipe_loop
**	
			ft_printf("Pipe detected! Multiple commands:\n");
**	
		ft_printf("No pipe detected. Single command:\n");
**	
*/

int	pipe_loop(t_vector *tokens, int size, char **envp)
{
	t_vector		pipes;
	int				ret;
	int				*pos;

	ret = 0;
	vector_init(&pipes, sizeof(int));
	if (load_pipe_vec(&pipes, tokens))
	{
		while (pipes.size > 1)
		{
			pos = (int *)pipes.data;
			ret = single_command(tokens, *pos + 1, *(pos + 1), envp);
			my_vector_pop_n(&pipes, 0, 1);
		}
	}
	else
	{
		ret = single_command(tokens, 0, size, envp);
	}
	return (vector_clear(&pipes), ret);
}
