/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:36:32 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/28 12:28:37 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"
#include "builtins.h"
#include "env_var.h"
#include "ft_printf.h"

static bool	export_arg_parse(char *arg, t_vector *env_vec)
{
	char	*buf;

	if (!arg[0] || arg[0] == '=')
	{
		ft_dprintf(2, "minishell: export: `%s': not a valid identifier\n",
			arg);
		return (1);
	}
	buf = next_non_identifier(arg);
	if (*buf == '=')
	{
		if (add_str_to_env_vec(env_vec, arg))
			return (1);
	}
	else if (*buf != '=' && *buf)
	{
		ft_dprintf(2, "minishell: export: `%s': not a valid identifier\n",
			arg);
		return (1);
	}
	return (0);
}

int	export_msh(char *execve_command, char **execve_com_args, t_vector *env_vec)
{
	bool	ret;
	int		i;

	(void) execve_command;
	ret = 0;
	i = 1;
	if (!execve_com_args[1])
		print_env_vec(env_vec, "export ");
	else
	{
		while (execve_com_args[i])
		{
			if (export_arg_parse(execve_com_args[i], env_vec))
				ret = 1;
			i++;
		}
	}
	return (ret);
}
