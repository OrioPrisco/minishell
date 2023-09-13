/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:33:20 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/13 16:15:56 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "child.h"
#include "libft.h"
#include "minishell.h"
#include "ft_printf.h"
#include "utils.h"
#include <stdlib.h>

/*
	NAME
		exit
	DESCRIPTION
		
	RETURN
		
*/

void	exit_msh(char *execve_command, char **execve_com_args, char **envp)
{
	(void) execve_command;
	(void) execve_com_args;
	(void) envp;
}

/*
	NAME
		echo
	DESCRIPTION
		
	RETURN
		
*/

void	echo(char *execve_command, char **execve_com_args, char **envp)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	(void) execve_command;
	(void) envp;
	if (!ft_strcmp(execve_com_args[1], "-n"))
	{
		i++;
		new_line = 0;
	}
	while (execve_com_args[i])
	{
		ft_printf("%s", execve_com_args[i]);
		i++;
		if (execve_com_args[i])
			ft_printf(" ");
	}
	if (new_line == 1)
		ft_printf("\n");
}

/*
	NAME
		builtin_commands
	DESCRIPTION
		
	RETURN
		
	NOTE
		Since execve is not being called, any leaks that happen will show up in
		valgrind.
		Make sure you check each builtin extensively for leaks.
*/

void	builtin_commands(char *execve_command, char **execve_com_args,
			char **envp)
{
	if (!ft_strcmp(execve_command, "echo"))
		echo(execve_command, execve_com_args, envp);
	if (!ft_strcmp(execve_command, "exit"))
	{
		table_free(execve_com_args);
		return ;
	}
	table_free(execve_com_args);
}
