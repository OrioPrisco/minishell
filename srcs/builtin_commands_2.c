/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:39:33 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/26 13:38:26 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "ft_printf.h"
#include "utils.h"
#include "error.h"
#include "env_var.h"

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

int	exit_msh(t_cominfo *cominfo, char **execve_com_args, int save_hist)
{
	char	*ptr;
	long	num;

	if (!execve_com_args[1])
	{
		table_free(execve_com_args);
		msh_exit(cominfo,
			cominfo->env_ret->prev_ret, save_hist);
	}
	if (execve_com_args[1] && execve_com_args[2])
		ft_dprintf(2, "minishell: exit: too many arguments\n");
	num = ft_strtol(execve_com_args[1], &ptr, 10);
	if (!ft_strtol_check_int(execve_com_args[1], ptr, num))
	{
		table_free(execve_com_args);
		msh_exit(cominfo, num, save_hist);
	}
	ft_dprintf(2, "minishell: exit: %s: numeric argument required\n",
		execve_com_args[1]);
	return (0);
}
