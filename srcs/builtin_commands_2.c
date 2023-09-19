/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:39:33 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/19 15:50:51 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "vector.h"
#include "ft_printf.h"
#include "utils.h"
#include "builtins.h"

int	unset_msh(char *execve_command, char **execve_com_args, t_vector *env_vec)
{
	(void) execve_command;
	(void) execve_com_args;
	(void) env_vec;
	ft_printf("You made it to unset_msh\n");
	table_print(execve_com_args);
	return (0);
}

int	env_msh(char *execve_command, char **execve_com_args, t_vector *env_vec)
{
	(void) execve_command;
	(void) execve_com_args;
	print_env_vec(env_vec, "");
	return (0);
}
