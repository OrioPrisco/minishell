/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:00:37 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/29 11:31:14 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_var.h"
#include <stdbool.h>
#include "ft_printf.h"
#include "libft.h"
#include "minishell.h"
#include "unistd.h"
#include "vector.h"
#include "tokens.h"

/*	*** table_free (table free) ***
 *
 *	Frees a char ** table created by ft_split.
 *	Takes a table to free 'table'.
 *	Returns nothing.
 */

void	table_free(char **table)
{
	int	i;

	i = 0;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
	return ;
}

/*
**	add_slash_and_comment
**	
*/

bool	add_slash_and_comment(char **path, int i, char *command)
{
	char	*slash_command;
	char	*new_path;

	slash_command = ft_strjoin("/", command);
	if (!slash_command)
		return (1);
	new_path = ft_strjoin(path[i], slash_command);
	if (!new_path)
		return (1);
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
		if (add_slash_and_comment(path, i, command))
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

/*
**	add_command_to_path
**		Adds the command from the single_command function to the end of each 
		item in the path variable so it can be run through the access function.
*/

bool	add_command_to_path(t_vector *tokens, int start, char **path)
{
	char	*command;
	int		i;

	i = 0;
	command = ((t_owned_token *)tokens->data + start)->str;
	while (path[i])
	{
		if (add_command_to_single_path_item(path, i, command))
			return (1);
		i++;
	}
	return (0);
}

/*	
**	RETURN
**		Returns NULL if malloc error while working or returns char * on success.
		Will also return NULL if no executable is found in path.
**	
**/

char	*access_loop(t_vector *tokens, int start, char **envp)
{
	const char	*env;
	char		**path;
	int			i;
	char		*ret_str;

	i = 0;
	ret_str = 0;
	env = get_env_var(envp, "PATH", 4);
	path = ft_split(env, ':');
	if (add_command_to_path(tokens, start, path))
		return (0);
	while (path[i])
	{
		if (access(path[i], F_OK | X_OK) == 0)
		{
			ret_str = ft_strdup(path[i]);
			break ;
		}
		i++;
	}
	table_free(path);
	return (ret_str);
}
