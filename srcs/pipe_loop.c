/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 07:51:09 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/21 07:56:12 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	check_for_pipe
**	
*/

bool	check_for_pipe(t_vector *tokens, int size)
{
	int				i;
	t_owned_token	*current;

	i = 0;
	while (i < size)
	{
		current = (t_owned_token *)tokens->data + i;
		if (current->type == T_PIPE)
			return (1);
		i++;
	}
	return (0);
}
