/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_chk_sel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:33:20 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/15 16:06:48 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "child.h"
#include "libft.h"
#include "minishell.h"
#include "ft_printf.h"
#include "utils.h"
#include <stdlib.h>
#include "builtins.h"
#include "env_var.h"

bool	check_for_builtins_pre_fork(t_com_segment com_segment)
{
	char	*exec_name;

	exec_name = get_exec_name(
			(t_owned_token *)com_segment.tokens->data + com_segment.start);
	if (!exec_name)
		return (0);
	if (0
		|| !ft_strcmp(exec_name, "cd")
		|| !ft_strcmp(exec_name, "pwd")
		|| !ft_strcmp(exec_name, "export")
		|| !ft_strcmp(exec_name, "exit"))
	{
		return (1);
	}
	return (0);
}

int	builtins_pre_fork(t_com_segment com_segment, t_cominfo *cominfo)
{
	char	**execve_com_args;
	char	*exec_name;
	int		ret;

	ret = 0;
	exec_name = get_exec_name(
			(t_owned_token *)com_segment.tokens->data + com_segment.start);
	if (!exec_name)
		return (-1);
	if (!ft_strcmp(exec_name, "exit"))
		exit_msh(cominfo, &com_segment);
	execve_com_args = construct_execve_args(com_segment);
	if (!execve_com_args)
		msh_error("malloc");
	if (!ft_strcmp(exec_name, "cd"))
		ret = cd_msh(exec_name, execve_com_args,
				(char **)cominfo->env_ret->env_vec.data);
	else if (!ft_strcmp(exec_name, "pwd"))
		ret = pwd_msh(exec_name, execve_com_args,
				(char **)cominfo->env_ret->env_vec.data);
	else if (!ft_strcmp(exec_name, "export"))
		ret = export_msh(exec_name, execve_com_args,
				(char **)cominfo->env_ret->env_vec.data);
	return (table_free(execve_com_args), ret);
}

int	check_for_builtins(const char *exec_name)
{
	if (0
		|| !ft_strcmp(exec_name, "echo")
		|| !ft_strcmp(exec_name, "cd")
		|| !ft_strcmp(exec_name, "pwd")
		|| !ft_strcmp(exec_name, "export")
		|| !ft_strcmp(exec_name, "unset")
		|| !ft_strcmp(exec_name, "env")
		|| !ft_strcmp(exec_name, "exit"))
		return (1);
	return (0);
}

int	builtin_commands(char *execve_command, char **execve_com_args,
			char **envp)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp(execve_command, "echo"))
		ret = echo_msh(execve_command, execve_com_args, envp);
	if (!ft_strcmp(execve_command, "cd"))
		ret = cd_msh(execve_command, execve_com_args, envp);
	if (!ft_strcmp(execve_command, "pwd"))
		ret = pwd_msh(execve_command, execve_com_args, envp);
	if (!ft_strcmp(execve_command, "export"))
		ret = export_msh(execve_command, execve_com_args, envp);
	if (!ft_strcmp(execve_command, "unset"))
		ret = unset_msh(execve_command, execve_com_args, envp);
	if (!ft_strcmp(execve_command, "env"))
		ret = env_msh(execve_command, execve_com_args, envp);
	if (!ft_strcmp(execve_command, "exit"))
		return (table_free(execve_com_args), 0);
	return (table_free(execve_com_args), ret);
}

void	builtins_cleanup(t_cominfo *cominfo, t_com_segment *com_seg, int ret)
{
	vector_free(com_seg->tokens, free_owned_token);
	vector_free(&cominfo->env_ret->env_vec, free_str);
	msh_exit_child(cominfo->com_list, ret);
}
