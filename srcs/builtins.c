/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:33:20 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/01 15:07:41 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"

/*
	NAME
		builtin_commands
	DESCRIPTION
		
	RETURN
		
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
	ft_printf("You entered a builtin!\n");
}
