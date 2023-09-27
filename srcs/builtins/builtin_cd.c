/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:47:39 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/27 17:32:58 by dpentlan         ###   ########.fr       */
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

char	*cd_getcwd(t_vector *env_vec)
{
	char	*ret;
	char	*cwd;

	cwd = (char *)get_env_var_no_special(env_vec->data, "PWD", 3);
	if (!cwd)
	{
		ret = getcwd(NULL, 0);
		if (!ret)
			return (ft_strdup(""));
	}
	else
		return (ft_strdup(cwd));
	return (ret);
}

int	cd_impl(const char *path, t_vector *env_vec, int print_cwd)
{
	char		*cwd;
	int			ret;

	cwd = cd_getcwd(env_vec);
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
	if (print_cwd)
		ft_printf("%s\n", cwd);
	return (free(cwd), 0);
}

int	cd_arg_parse_msh(char **execve_com_args, t_vector *env_vec)
{
	int			ret;
	int			print_cwd;
	const char	*path;

	print_cwd = 0;
	if (execve_com_args[1] && execve_com_args[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	path = execve_com_args[1];
	if (!execve_com_args[1])
	{
		path = get_env_var_no_special(env_vec->data, "HOME", 4);
		if (!path)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
		if (!ft_strcmp(path, ""))
			return (0);
	}
	else if (!ft_strcmp(execve_com_args[1], "-"))
	{
		path = get_env_var_no_special(env_vec->data, "HOME", 4);
		if (!path)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
		print_cwd = 1;
	}
	else if (!ft_strcmp(execve_com_args[1], "--"))
	{
		path = get_env_var_no_special(env_vec->data, "HOME", 4);
		if (!path)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
		if (!ft_strcmp(path, ""))
			return (0);
	}
	else if (!ft_strcmp(execve_com_args[1], "---"))
		return (ft_putstr_fd("minishell: cd: --: invalid option\n", 2), 2);
	ret = cd_impl(path, env_vec, print_cwd);
	return (ret);
}
