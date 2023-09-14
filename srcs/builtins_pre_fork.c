/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pre_fork.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:52:13 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/14 13:08:12 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "vector.h"
#include "ft_printf.h"

void	cd_pre_fork(void)
{
	return ;
}

void	pwd_pre_fork(void)
{
	ft_printf("You made it to pwd_pre_fork\n");
}

void	export_pre_fork(void)
{
	ft_printf("You made it to export_pre_fork\n");
}

void	exit_pre_fork(t_cominfo *cominfo, t_com_segment *com_segment)
{
	vector_free(com_segment->tokens, free_owned_token);
	msh_exit(cominfo);
}

int	builtins_pre_fork(char *exec_name, t_com_segment com_segment,
					t_cominfo *cominfo)
{
	if (!ft_strcmp(exec_name, "cd"))
		cd_pre_fork();
	else if (!ft_strcmp(exec_name, "pwd"))
		pwd_pre_fork();
	else if (!ft_strcmp(exec_name, "export"))
		export_pre_fork();
	else if (!ft_strcmp(exec_name, "exit"))
		exit_pre_fork(cominfo, &com_segment);
	return (0);
}
