/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:58:47 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/18 15:42:10 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "vector.h"
#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

static void	free_command_vector(t_vector *com_list)
{
	size_t	i;

	i = 0;
	while (i < com_list->size)
	{
		free(((char **)com_list->data)[i]);
		i++;
	}
	vector_clear(com_list);
}

void	msh_error(const char *message)
{
	if (message)
		perror(message);
	else
		ft_putstr_fd("Error:", 2);
	exit(EXIT_FAILURE);
}

void	msh_exit(char **env, t_vector *com_list)
{
	save_history(env, com_list);
	free_command_vector(com_list);
	ft_putstr_fd("exit\n", 1);
	exit(EXIT_SUCCESS);
}
