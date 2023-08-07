/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:02:35 by dpentlan          #+#    #+#             */
/*   Updated: 2023/08/07 16:48:52 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"
#include <stdlib.h>
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
		exec_rel_path
	DESCRIPTION
		Checks if the command is a relative path which means we should create a
			path to return.
		If not, we return NULL which tells the calling function we should check
			the PATH variable instead.
	RETURN
		Returns a malloced string which contains the abs path of the command
			to execute.
		Returns NULL in case of malloc error or command is not a relative path.
*/

char	*exec_rel_path(const char *exec_name)
{
	char	*cwd;

	cwd = NULL;
	if (exec_name[0] != '.' && exec_name[0] != '/')
		return (NULL);
	cwd = getcwd(cwd, 0);
	// create an abs path from your relative paths.
	ft_printf("cwd = %s\n", cwd);
	free(cwd);
	return (NULL);
}
