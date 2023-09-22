/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:39:33 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/22 15:00:36 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"

int	unset_msh(char *execve_command, char **execve_com_args, t_vector *env_vec)
{
	size_t	str_len;

	(void) execve_command;
	if (!execve_com_args[1])
		return (0);
	str_len = ft_strlen(execve_com_args[1]);
	if (!str_len)
		return (0);
	execve_com_args[1][str_len] = '=';
	del_from_env_vec(env_vec,
		check_env_vec_dup(env_vec, execve_com_args[1], str_len));
	execve_com_args[1][str_len] = 0;
	return (0);
}

int	env_msh(char *execve_command, char **execve_com_args, t_vector *env_vec)
{
	(void) execve_command;
	(void) execve_com_args;
	print_env_vec(env_vec, "");
	return (0);
}
