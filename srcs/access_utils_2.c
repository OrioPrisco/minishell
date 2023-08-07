/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:02:35 by dpentlan          #+#    #+#             */
/*   Updated: 2023/08/07 17:57:22 by dpentlan         ###   ########.fr       */
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
**	NAME
		*create_abs_path_from_rel_path
**	DESCRIPTION
		
**	RETURN
		
*/

char	*create_abs_path_from_rel_path(char *cwd, char *exec_name)
{
	//	ft_split cwd to get a table of directories
	//	ft_split exec_name to get things to add or subtract from command
	//	Enter loop where if we find a .. in exec_name we subtract a directory
	//		if we find a . we do nothing
	//		if we find a string we add that to the end of the table/vector.
	//	check access of the abs path at the end. Should be executable.
	return (0);
}

/*
	NAME
		exec_rel_path
	DESCRIPTION
		Checks if the command is a relative path which means we should create a
			path to return. paths should start with / or .
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
	char	*abs_path_com;

	cwd = NULL;
	if (exec_name[0] != '.' && exec_name[0] != '/')
		return (NULL);
	cwd = getcwd(cwd, 0);
	abs_path_com = create_abs_path_from_rel_path(cwd, exec_name);
	if (!abs_path_com)
		return (NULL);
	ft_printf("cwd = %s\n", cwd);
	free(cwd);
	return (NULL);
}
