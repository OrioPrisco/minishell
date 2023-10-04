/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_chk_sel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:33:20 by dpentlan          #+#    #+#             */
/*   Updated: 2023/10/04 19:24:04 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utils.h"
#include "builtins.h"
#include "env_var.h"
#include "vector.h"
#include "tokens.h"
#include "error.h"
#include "child.h"
#include <unistd.h>

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

bool	prefork_redirects(t_com_segment *com_segment, t_cominfo *cominfo,
					char *exec_name, char **execve_com_args)
{
	int			ret;
	t_vector	vec_fds;
	int			original_stdout;

	original_stdout = dup(STDOUT_FILENO);
	vector_init(&vec_fds, sizeof(int));
	ret = check_and_open_redirects(com_segment->tokens, &vec_fds,
			com_segment->start, com_segment->stop);
	if (ret)
		return (table_free(execve_com_args), close(original_stdout), ret == 1);
	open_heredocs(com_segment->tokens->data, com_segment->start,
		com_segment->stop);
	if (vec_fds.size > 0)
		dup2(((int *)vec_fds.data)[vec_fds.size - 1], 1);
	close(1);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
	vector_free(&vec_fds, close_fd);
	cominfo->env_ret->prev_ret = builtin_commands(exec_name,
			execve_com_args, cominfo);
	return (0);
}

bool	builtins_pre_fork(t_com_segment com_segment, t_cominfo *cominfo)
{
	char		**execve_com_args;
	char		*exec_name;

	exec_name = get_exec_name(
			(t_owned_token *)com_segment.tokens->data + com_segment.start);
	if (!exec_name)
		return (1);
	execve_com_args = construct_execve_args(com_segment);
	if (!execve_com_args)
		return (msh_error("malloc"), 1);
	return (prefork_redirects(&com_segment, cominfo, exec_name,
			execve_com_args));
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
		ret = cd_arg_parse_msh(execve_com_args, &cominfo->env_ret->env_vec);
	else if (!ft_strcmp(execve_command, "pwd"))
		ret = pwd_msh(execve_command, execve_com_args,
				&cominfo->env_ret->env_vec);
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
