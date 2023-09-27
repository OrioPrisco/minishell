/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:47:39 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/27 14:53:49 by dpentlan         ###   ########.fr       */
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

int	cd_impl(const char *path, t_vector *env_vec)
{
	char		*cwd;
	int			ret;

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
	return (free(cwd), 0);
}

int	cd_arg_parse_msh(char **execve_com_args, t_vector *env_vec)
{
	int			ret;
	const char	*path;

	if (execve_com_args[2])
		return (ft_putstr_fd("minishell: cd: too many arguments", 2), 1);
	path = execve_com_args[1];
	if (!execve_com_args[1])
	{
		path = get_env_var_no_special(env_vec->data, "HOME", 4);
		if (!path)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	}
	ret = cd_impl(path, env_vec);
	return (ret);
}
