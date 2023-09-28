/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:36:32 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/27 13:47:04 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"
#include "builtins.h"
#include "env_var.h"
#include "ft_printf.h"

int	export_msh(char *execve_command, char **execve_com_args, t_vector *env_vec)
{
	char	*buf;

	(void) execve_command;
	if (!execve_com_args[1])
		print_env_vec(env_vec, "export ");
	else
	{
		buf = next_non_identifier(execve_com_args[1]);
		if (*buf == '=' && *ft_strpbrknul(buf + 1, "= \t") == '\0')
		{
			if (add_str_to_env_vec(env_vec, execve_com_args[1]))
				return (-1);
		}
		else if (*buf != '=' && *buf)
		{
			ft_dprintf(2, "minishell: export: `%s': not a valid identifier\n",
				execve_com_args[1]);
		}
	}
	return (0);
}
