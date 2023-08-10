/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:02:35 by dpentlan          #+#    #+#             */
/*   Updated: 2023/08/10 10:22:07 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"
#include "utils.h"
#include <unistd.h>

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
	if (is_directory(exec_name))
		ft_dprintf(2, "%s: Is a directory\n", exec_name);
	else if (access(exec_name, F_OK | X_OK))
		ft_dprintf(2, "%s: Permission denied\n", exec_name);
	else
		ft_dprintf(2, "%s: command not found\n", exec_name);
}
