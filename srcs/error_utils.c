/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:58:47 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/22 14:38:59 by dpentlan         ###   ########.fr       */
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
}

void	msh_exit(t_cominfo *cominfo, int ret_code, int save_his)
{
	if (save_his)
	{
		ft_putstr_fd("exit\n", 1);
		save_history(cominfo->env_ret, &cominfo->com_list);
	}
	if (cominfo->tokens)
		vector_free(cominfo->tokens, free_owned_token);
	vector_free(&cominfo->com_list, free_str);
	vector_free(&cominfo->env_ret->env_vec, free_str);
	exit(ret_code);
}
