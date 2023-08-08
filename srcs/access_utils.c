/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:00:37 by dpentlan          #+#    #+#             */
/*   Updated: 2023/08/08 16:23:48 by dpentlan         ###   ########.fr       */
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
		*get_exec_name
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

static const char	*get_exec_name(t_owned_token *token)
{
	while (token->type != T_END && token->type != T_PIPE)
	{
		if (is_redirect_type(token->type))
			token ++;
		else if (token->type == T_STR)
			return (token->str);
		token++;
	}
	return (NULL);
}

/*
**	NAME
		check_access
**	DESCRIPTION
		Takes a command and a path,
		and iterates over table searching for access.
**	RETURN
		Returns malloced string containing the abs path and command if one is 
		found in path if access is found.
		Returns malloced empty string if access is never found.
		Returns NULL if malloc error.
*/

static char	*check_access(const char *const *path, const char *command)
{
	char	*temp;

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
		Returns a malloced string containing the abs path and process name of the 
		command the user entered. 
		Returns an empty string if no access is found. 
		Returns NULL if malloc error.
**	
**/

char	*access_loop(const char *command, char **envp)
{
	char		**path_tab;
	const char	*path;
	char		*command_path;

	path = get_env_var(envp, "PATH", ft_strlen("PATH"));
	if (!path)
		return (0);
	path_tab = ft_split(path, ':');
	if (!path_tab)
		return (0);
	command_path = check_access((const char **)path_tab, command);
	return (table_free(path_tab), command_path);
}

/*
	NAME
		find_executable
	DESCRIPTION
		Looks for abs path of executable command.
		First looks in the command itself looking for a relative path.
		if no releative path is found, we check for the executable in the PATH
		varaible with the access_loop function.
		If nothing is found by the end, we print 'command not found' and
		return NULL
	RETURN
		Returns a malloced string containing the abs path of the command to
		execute.
		Returns NULL in case of no executaeble found, or no command given,
		or malloc error inside of a function.
*/

char	*find_executable(t_cominfo *cominfo, t_com_segment com_segment)
{
	char			*execve_command;
	const char		*exec_name;

	exec_name = get_exec_name(
			(t_owned_token *)com_segment.tokens->data + com_segment.start);
	if (!exec_name)
		return (NULL);
	execve_command = access_loop(exec_name, cominfo->envp);
	if (!execve_command)
		return (NULL);
	if (!execve_command[0])
	{
		ft_dprintf(2, "command not found: %s\n", exec_name);
		return (free(execve_command), NULL);
	}
	return (execve_command);
}
