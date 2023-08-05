/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:58:47 by dpentlan          #+#    #+#             */
/*   Updated: 2023/08/05 15:14:15 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "vector.h"
#include <stdlib.h>
#include "libft.h"
#include <stdio.h>
#include "utils.h"

void	msh_error(const char *message)
{
	if (message)
		perror(message);
	else
		ft_putstr_fd("Error:", 2);
	exit(EXIT_FAILURE);
}

void	msh_exit(char **envp, t_vector *com_list)
{
	save_history(envp, com_list);
	vector_free(com_list, free_str);
	ft_putstr_fd("exit\n", 1);
	exit(EXIT_SUCCESS);
}

void	msh_exit_child(char **envp, t_vector *com_list)
{
	save_history(envp, com_list);
	vector_free(com_list, free_str);
	exit(EXIT_SUCCESS);
}
