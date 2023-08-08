/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:00:37 by dpentlan          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/08/08 16:09:12 by dpentlan         ###   ########.fr       */
=======
/*   Updated: 2023/08/07 21:41:01 by OrioPrisco       ###   ########.fr       */
>>>>>>> 64e8ff1 (Modifying access to work with new code.)
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
#include "path.h"

/*
**	NAME
		*get_process_name
**	DESCRIPTION
		Starting from token provided, searches until T_END or T_PIPE for a T_STR
		jumping over any other token (ie. T_REDIRECT_STDIN, T_REDIRECT_APPEND_STDIN,
		T_REDIRECT_APPEND_STDOUT, T_HEREDOC)
**	RETURN
		Returns a non malloced string containing the command.
		Returns an empty string if no command is found. (ie. '<< heredoc' is a valid
		command)
		Returns NULL if malloc error.
*/

static const char	*get_process_name(t_owned_token *token)
{
	while (token->type != T_END && token->type != T_PIPE)
	{
		if (is_redirect_type(token->type))
			token ++;
		else if (token->type == T_STR)
			return (token->str);
		token++;
	}
	return ("");
}

/*
**	NAME
		check_access
**	DESCRIPTION
		Takes a command and a path,
		and iterates over table searching for access.
**	RETURN
		Returns malloced string containing either a copy of the command
		if contains a slash and access is found or
		the abs path and command if one is 
		found in path if access is found.
		Returns malloced empty string if access is not found.
		Returns NULL if malloc error.
*/

static char	*check_access(const char *const *path, const char *command)
{
	char	*temp;

	if (ft_strchr(command, '/'))
	{
		if (!access(command, F_OK | X_OK))
			return (ft_strdup(command));
		return (ft_strdup(""));
	}
	while (*path)
	{
		temp = path_concat(*path, command);
		if (!temp)
			return (NULL);
		if (!access(temp, F_OK | X_OK))
			return (temp);
		free(temp);
		path++;
	}
	return (ft_strdup(""));
}

/*	
**	NAME
		access_loop
**	DESCRIPTION
		Gets the name of the process from the list of token provided.
		Then builds a list of all possible paths based on PATH environment variable.
		Finally checks access for command in built list of paths.
**	RETURN
		Returns a malloced string containing the abs or relative path of the 
		command the user entered. 
		Returns an empty string if no access is found. 
		Returns NULL if malloc error.
**	
**/

char	*access_loop(t_owned_token *tokens, char **envp)
{
	char		**path_tab;
	const char	*path;
	const char	*command;
	char		*command_path;

	path = get_env_var(envp, "PATH", ft_strlen("PATH"));
	if (!path)
		return (0);
	command = get_process_name(tokens);
	if (!command)
		return (0);
	if (!command[0])
		return (ft_strdup(command));
	path_tab = ft_split(path, ':');
	if (!path_tab)
		return (0);
	command_path = check_access((const char **)path_tab, command);
	table_free(path_tab);
	return (command_path);
}
