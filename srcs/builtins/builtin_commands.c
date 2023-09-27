/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:52:13 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/27 13:45:56 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "unistd.h"
#include "builtins.h"
#include "env_var.h"
#include <stdlib.h>
#include "error.h"
#include "utils.h"

int	cd_msh(char **execve_com_args, t_vector *env_vec)
{
	int			ret;
	const char	*path;
	char		*cwd;

	path = execve_com_args[1];
	if (!execve_com_args[1])
	{
		path = get_env_var_no_special(env_vec->data, "HOME", 4);
		if (!path)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (msh_error("malloc"), -1);
	if (chdir(path))
		return (msh_error(path), free(cwd), 1);
	ret = add_key_value_to_env_vec("OLDPWD=", cwd, env_vec);
	if (ret)
		return (free(cwd), ret);
	free(cwd);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (msh_error("malloc"), -1);
	ret = add_key_value_to_env_vec("PWD=", cwd, env_vec);
	return (free(cwd), ret);
}

int	pwd_msh(char *execve_command, char **execve_com_args, char **envp)
{
	char	*cwd;

	cwd = 0;
	(void) execve_command;
	(void) execve_com_args;
	(void) envp;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (msh_error("getcwd"), -1);
	ft_printf("%s\n", cwd);
	free(cwd);
	return (0);
}

static int	echo_arg_parsing(char **execve_com_args, int *nl_flag)
{
	int	i;
	int	j;

	i = 0;
	execve_com_args++;
	while (execve_com_args[i])
	{
		j = 0;
		if (execve_com_args[i][j] != '-' || execve_com_args[i][j + 1] != 'n')
			break ;
		j++;
		j += ft_strspn(&execve_com_args[i][j], "n");
		if (execve_com_args[i][j] == '\0')
			i++;
		else
			break ;
	}
	if (i > 0)
		*nl_flag = 0;
	return (i);
}

int	echo_msh(char *execve_command, char **execve_com_args, char **envp)
{
	int	i;
	int	new_line;

	(void) execve_command;
	(void) envp;
	i = 1;
	new_line = 1;
	i += echo_arg_parsing(execve_com_args, &new_line);
	while (execve_com_args[i])
	{
		ft_printf("%s", execve_com_args[i]);
		i++;
		if (execve_com_args[i])
			ft_printf(" ");
	}
	if (new_line == 1)
		ft_printf("\n");
	return (0);
}
