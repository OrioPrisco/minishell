/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:02:35 by dpentlan          #+#    #+#             */
/*   Updated: 2023/08/03 13:06:17 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

/*
**	add_slash_and_comment
**	
*/

bool	add_slash_and_command(char **path, int i, char *command)
{
	char	*slash_command;
	char	*new_path;

	if (!command)
		return (1);
	slash_command = ft_strjoin("/", command);
	if (!slash_command)
		return (1);
	new_path = ft_strjoin(path[i], slash_command);
	if (!new_path)
		return (free(slash_command), 1);
	free(slash_command);
	free(path[i]);
	path[i] = new_path;
	return (0);
}

/*
**	add_command_to_single_path_item
**	
*/

bool	add_command_to_single_path_item(char **path, int i, char *command)
{
	char	*new_path;
	int		j;

	j = 0;
	while (path[i][j])
		j++;
	if (path[i][j - 1] != '/')
	{
		if (add_slash_and_command(path, i, command))
			return (1);
	}
	else
	{
		new_path = ft_strjoin(path[i], command);
		if (!new_path)
			return (1);
		free(path[i]);
		path[i] = new_path;
	}
	return (0);
}

void	print_access_debug(char *execve_command)
{
	if (!execve_command[0])
		ft_printf("no access found\n");
	else
		ft_printf("access found\n");
}
