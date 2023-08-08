/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:02:35 by dpentlan          #+#    #+#             */
/*   Updated: 2023/08/08 14:29:39 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

void	print_access_debug(char *execve_command)
{
	if (!execve_command[0])
		ft_printf("no access found\n");
	else
		ft_printf("access found\n");
}

/*
	NAME
		check_com_dir
	DESCRIPTION
		using stat, fstat, or lstat. stat will dereference symbolic links,
			fstat will take an open fd, and lstat will return info on a symbolic
			link.
	RETURN
		
*/

int	check_com_stat(const char *exec_name)
{
	char		**exec_tab;
	int			ret;
	struct stat	stat_buf;

	ret = 0;
	exec_tab = ft_split(exec_name, '/');
	if (!exec_tab)
		return (-1);
	ret = stat(exec_name, &stat_buf);
	ft_printf("ret from stat: %d\n", ret);
	ft_printf("stat_buf.st_mode: %d", stat_buf.st_mode);
	return (-1);
}

/*
	NAME
		exec_rel_path
	DESCRIPTION
		Checks access for the input (relative paths), and checks that the first
			item in the command list is a directory.
	RETURN
		Returns 0 on success and -1 on fail exactly like the access function.
		See man 3 access for more info.
*/

int	exec_rel_path(const char *exec_name)
{
	if (!access(exec_name, X_OK) && check_com_stat(exec_name))
		return (0);
	return (-1);
}
