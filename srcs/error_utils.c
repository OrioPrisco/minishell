/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:58:47 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/06 14:12:25 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_command_vector(t_vector *com_list)
{
	size_t	i;

	i = 0;
	while (i < com_list->size)
	{
		free(((char **)com_list->data)[i]);
		i++;
	}
	free(com_list->data);
	free(com_list);
	return (0);
}

void	msh_error(char *message)
{
	if (message)
		perror(message);
	else
		ft_putstr_fd("Error:", 2);
	exit(EXIT_FAILURE);
}

void	msh_exit(t_vector *com_list)
{
	save_history(com_list);
	free_command_vector(com_list);
	ft_putstr_fd("exit\n", 1);
	exit(EXIT_SUCCESS);
}
