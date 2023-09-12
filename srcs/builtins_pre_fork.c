/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pre_fork.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:52:13 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/12 15:34:41 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "vector.h"

void	exit_pre_fork(t_cominfo *cominfo)
{
	msh_exit(cominfo);
}

void	builtins_pre_fork(char *exec_name, t_com_segment com_segment,
					t_cominfo *cominfo)
{
	(void) com_segment;
	if (!ft_strcmp(exec_name, "exit"))
		exit_pre_fork(cominfo);
}
