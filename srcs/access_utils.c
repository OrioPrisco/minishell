/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:00:37 by dpentlan          #+#    #+#             */
/*   Updated: 2023/08/03 13:16:10 by dpentlan         ###   ########.fr       */
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
#include "utils.h"

/*
**	add_command_to_path
**		Adds the command from the single_command function to the end of each 
		item in the path variable so it can be run through the access function.
*/

bool	add_command_to_path(char *command, char **path)
{
	int		i;

	i = 0;
	while (path[i])
	{
		if (add_command_to_single_path_item(path, i, command))
			return (1);
		i++;
	}
	return (0);
}

/*
**	NAME
		*get_path_with_commands
**	DESCRIPTION
		Gets path from environment variables, splits by ':', then takes the table from 
		ft_split and adds 'command' or '/command' to the end.
**	RETURN
		Returns a freeable table with command added to the end of each item in PATH.
		Returns NULL on error.
*/

char	**get_path_with_commands(char *command, char **path, char **envp)
{
	const char	*env;

	if (path)
		return (0);
	env = get_env_var(envp, "PATH", 4);
	if (!env)
		return (0);
	path = ft_split(env, ':');
	if (!path)
		return (0);
	if (add_command_to_path(command, path))
	{
		table_free(path);
		return (0);
	}
	return (path);
}

/*
**	NAME
		*get_process_name
**	DESCRIPTION
		Starting from token provided, searches until T_END or T_PIPE for a T_STR
		jumping over any other token (ie. T_REDIRECT_STDIN, T_REDIRECT_APPEND_STDIN,
		T_REDIRECT_APPEND_STDOUT, T_HEREDOC)
**	RETURN
		Returns a malloced string containing the command.
		Returns an empty string if no command is found. (ie. '<< heredoc' is a valid
		command)
		Returns NULL if malloc error.
*/

char	*get_process_name(t_owned_token *token)
{
	char	*ret_str;

	ret_str = 0;
	ret_str = (char *)malloc(sizeof(char) * 1);
	if (!ret_str)
		return (0);
	ret_str[0] = 0;
	while (token->type != T_END && token->type != T_PIPE)
	{
		if (token->type == T_STR)
		{
			free(ret_str);
			ret_str = ft_strdup(token->str);
			if (!ret_str)
				return (0);
			return (ret_str);
		}
		token++;
		if (token->type == T_END || token->type == T_PIPE)
			return (ret_str);
		token++;
	}
	return (ret_str);
}

/*
**	NAME
		check_access
**	DESCRIPTION
		Takes a path (with commands appended to the end of each member) and
		iterates over table searching for access.
**	RETURN
		Returns malloced string containing the abs path and command if one is 
		found in path if access is found.
		Returns malloced empty string if access is never found.
		Returns NULL if malloc error.
*/

char	*check_access(char **path)
{
	int		i;
	char	*ret_str;

	i = 0;
	ret_str = 0;
	ret_str = (char *)malloc(sizeof(char) * 1);
	if (!ret_str)
		return (0);
	ret_str[0] = 0;
	while (path[i])
	{
		if (access(path[i], F_OK | X_OK) == 0)
		{
			free(ret_str);
			ret_str = ft_strdup(path[i]);
			if (!ret_str)
				return (0);
			break ;
		}
		i++;
	}
	return (ret_str);
}

/*	
**	NAME
		access_loop
**	DESCRIPTION
		Gets the name of the process from the token provided.
		Then builds a list of all possible paths based on PATH environment variable.
		Finally checks access for command in built list of paths.
**	RETURN
		Returns a malloced string containing the abs path and process name of the 
		command the user entered. 
		Returns an empty string if no access is found. 
		Returns NULL if malloc error.
**	
**/

char	*access_loop(t_owned_token *token, char **envp)
{
	char		**path;
	char		*command;

	path = 0;
	command = 0;
	command = get_process_name(token);
	if (!command)
		return (0);
	if (!command[0])
		return (command);
	path = get_path_with_commands(command, path, envp);
	free(command);
	if (!path)
		return (0);
	command = check_access(path);
	if (!command)
		return (0);
	table_free(path);
	return (command);
}
