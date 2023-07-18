/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:58:47 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/18 17:01:49 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "vector.h"
#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

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
	vector_free(com_list, free);
	ft_putstr_fd("exit\n", 1);
	exit(EXIT_SUCCESS);
}
