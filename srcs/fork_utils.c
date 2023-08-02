/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:46:45 by dpentlan          #+#    #+#             */
/*   Updated: 2023/08/02 19:12:08 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "vector.h"

/*
**	msh_wait
**	
*/

int	msh_wait(t_vector *pids)
{
	while (pids->size > 0)
	{
		waitpid(((int)pids->data + pids->size), NULL, 0);
		vector_pop_n(pids, pids->size, 1);
	}
	return (0);
}
