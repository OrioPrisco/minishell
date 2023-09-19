/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:39:33 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/18 15:50:55 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "vector.h"
#include "ft_printf.h"
#include "utils.h"

int	unset_msh(char *execve_command, char **execve_com_args, char **envp)
{
	(void) execve_command;
	(void) execve_com_args;
	(void) envp;
	ft_printf("You made it to unset_msh\n");
	table_print(execve_com_args);
	return (0);
}

int	env_msh(char *execve_command, char **execve_com_args, char **envp)
{
	(void) execve_command;
	(void) execve_com_args;
	(void) envp;
	ft_printf("You made it to env_msh\n");
	table_print(execve_com_args);
	return (0);
}
