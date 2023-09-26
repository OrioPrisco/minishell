/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_chk_sel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:33:20 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/26 13:18:41 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "builtins.h"
#include "env_var.h"
#include "ft_readline.h"
#include "vector.h"
#include "tokens.h"
#include "error.h"

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
		|| !ft_strcmp(exec_name, "exit")
		|| !ft_strcmp(exec_name, "env")
		|| !ft_strcmp(exec_name, "unset"))
	{
		return (1);
	}
	return (0);
}

int	builtins_pre_fork(t_com_segment com_segment, t_cominfo *cominfo)
{
	char	**execve_com_args;
	char	*exec_name;

	exec_name = get_exec_name(
			(t_owned_token *)com_segment.tokens->data + com_segment.start);
	if (!exec_name)
		return (-1);
	execve_com_args = construct_execve_args(com_segment);
	if (!execve_com_args)
		return (msh_error("malloc"), -1);
	if (!ft_strcmp(exec_name, "exit"))
		exit_msh(cominfo, execve_com_args, 1);
	return (builtin_commands(exec_name, execve_com_args, cominfo));
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
			t_cominfo *cominfo)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp(execve_command, "echo"))
		ret = echo_msh(execve_command, execve_com_args,
				cominfo->env_ret->env_vec.data);
	else if (!ft_strcmp(execve_command, "cd"))
		ret = cd_msh(execve_com_args, &cominfo->env_ret->env_vec);
	else if (!ft_strcmp(execve_command, "pwd"))
		ret = pwd_msh(execve_command, execve_com_args,
				cominfo->env_ret->env_vec.data);
	else if (!ft_strcmp(execve_command, "export"))
		ret = export_msh(execve_command, execve_com_args,
				&cominfo->env_ret->env_vec);
	else if (!ft_strcmp(execve_command, "unset"))
		ret = unset_msh(execve_command, execve_com_args,
				&cominfo->env_ret->env_vec);
	else if (!ft_strcmp(execve_command, "env"))
		ret = env_msh(execve_command, execve_com_args,
				&cominfo->env_ret->env_vec);
	else if (!ft_strcmp(execve_command, "exit"))
		ret = exit_msh(cominfo, execve_com_args, 0);
	return (table_free(execve_com_args), ret);
}

void	builtins_cleanup(t_cominfo *cominfo, t_com_segment *com_seg, int ret)
{
	vector_free(com_seg->tokens, free_owned_token);
	vector_free(&cominfo->env_ret->env_vec, free_str);
	ft_rl_clear(cominfo->rlinfo);
	msh_exit(cominfo, ret, 0);
}
