/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:02:35 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/15 12:42:17 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"
#include "path.h"
#include <unistd.h>
#include "vector.h"
#include <errno.h>

void	print_access_debug(char *execve_command)
{
	if (!execve_command[0])
		ft_printf("no access found\n");
	else
		ft_printf("access found\n");
}

/*
	NAME
		
	DESCRIPTION
		
	RETURN
		
*/

void	access_error_print(const char *exec_name)
{
	int	ret;

	if (ft_strchr(exec_name, '/'))
	{
		ret = is_directory(exec_name);
		if (ret == 1)
			ft_dprintf(2, "%s: Is a directory\n", exec_name);
		else if (ret == -1)
			msh_error(exec_name);
		else if (access(exec_name, F_OK | X_OK))
			msh_error(exec_name);
			//ft_dprintf(2, "%s: Permission denied\n", exec_name);
	}
	else
		ft_dprintf(2, "%s: command not found\n", exec_name);
}

/*
	NAME
		check_for_builtins
	DESCRIPTION
		
	RETURN
		
*/

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

int	check_for_builtins_pre_fork(t_com_segment com_segment, t_cominfo *cominfo)
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
		if (builtins_pre_fork(exec_name, com_segment, cominfo))
			return (-1);
	}
	return (0);
}
