/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:58:47 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/13 17:15:06 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "vector.h"
#include <stdlib.h>
#include "libft.h"
#include <stdio.h>
#include "utils.h"
#include "env_var.h"

void	msh_error(const char *message)
{
	ft_putstr_fd("minishell: ", 2);
	perror(message);
	exit(EXIT_FAILURE);
}

void	msh_exit(t_cominfo *cominfo)
{
	save_history(cominfo->env_ret, &cominfo->com_list);
	vector_free(&cominfo->com_list, free_str);
	vector_free(&cominfo->env_ret->env_vec, free_str);
	ft_putstr_fd("exit\n", 1);
	exit(EXIT_SUCCESS);
}
