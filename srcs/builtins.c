/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:33:20 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/01 15:22:18 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"
#include "utils.h"
#include <stdlib.h>

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
	if (execve_command)
	{
	}
	if (execve_com_args)
	{
	}
	if (envp)
	{
	}
	table_free(execve_com_args);
	free(execve_command);
	ft_printf("You entered a builtin!\n");
}
