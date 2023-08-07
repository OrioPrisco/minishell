/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:00:37 by dpentlan          #+#    #+#             */
/*   Updated: 2023/08/07 15:22:17 by dpentlan         ###   ########.fr       */
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

/*
**	*find_executable
**	
*/

char	*find_executable(t_cominfo *cominfo, t_com_segment com_segment)
{
	char			*execve_command;
	t_owned_token	*com_start;

	com_start = (t_owned_token *)com_segment.tokens->data + com_segment.start;
	execve_command = access_loop(com_start, cominfo->envp);
	if (!execve_command)
		return (0);
	if (!execve_command[0])
	{
		ft_dprintf(2, "command not found: %s\n",
			get_process_name(com_start));
		return (free(execve_command), NULL);
	}
	return (execve_command);
}
