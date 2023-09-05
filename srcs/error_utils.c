/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:58:47 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/05 16:43:36 by dpentlan         ###   ########.fr       */
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
	ft_putstr_fd("minishell: ", 2);
	perror(message);
	exit(EXIT_FAILURE);
}

void	msh_exit(char **envp, t_vector *com_list)
{
	save_history(envp, com_list);
	vector_free(com_list, free_str);
	ft_putstr_fd("exit\n", 1);
	exit(EXIT_SUCCESS);
}
