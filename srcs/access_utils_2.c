/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:02:35 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/22 16:04:34 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"
#include "path.h"
#include <unistd.h>
#include "vector.h"
#include "utils.h"
#include "env_var.h"
#include "child.h"
#include "tokens.h"
#include "error.h"

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
	}
	else
		ft_dprintf(2, "%s: command not found\n", exec_name);
}
