/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:52:13 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/21 16:27:26 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "vector.h"
#include "ft_printf.h"
#include "utils.h"
#include "unistd.h"
#include "builtins.h"
#include "env_var.h"

// needs to save old pwd to $OLDPWD and reassign $PWD to the new working dir.
// and go to home if no args given.

int	cd_msh(char *execve_command, char **execve_com_args, t_vector *env_vec)
{
	int			ret;
	const char	*path;

	(void) execve_command;
	if (!execve_com_args[1])
	{
		path = get_env_var_no_special(env_vec->data, "HOME", 4);
		if (!path)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	}
	else
		path = execve_com_args[1];
	ret = save_cwd_to_env_vec("OLDPWD=", env_vec);
	if (ret)
		return (ret);
	if (chdir(path))
		return (msh_error(""), 1);
	ret = save_cwd_to_env_vec("PWD=", env_vec);
	if (ret)
		return (ret);
	return (0);
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

int	export_msh(char *execve_command, char **execve_com_args, t_vector *env_vec)
{
	char	*buf;

	(void) execve_command;
	if (!execve_com_args[1])
		print_env_vec(env_vec, "declare -x ");
	else
	{
		buf = next_non_identifier(execve_com_args[1]);
		if (*buf == '=' && *ft_strpbrknul(buf + 1, "= \t") == '\0')
		{
			if (add_to_env_vec(env_vec, execve_com_args[1]))
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

void	exit_msh(t_cominfo *cominfo, t_com_segment *com_segment)
{
	vector_free(com_segment->tokens, free_owned_token);
	msh_exit(cominfo);
}

// echo should handle echo -nnn -nnnnnnn hi and return hi

int	echo_msh(char *execve_command, char **execve_com_args, char **envp)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (!execve_com_args[1])
		return (0);
	(void) execve_command;
	(void) envp;
	if (!ft_strcmp(execve_com_args[1], "-n"))
	{
		i++;
		new_line = 0;
	}
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
