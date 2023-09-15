/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:52:13 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/15 17:19:09 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "vector.h"
#include "ft_printf.h"
#include "utils.h"
#include "unistd.h"

// needs to save old pwd to $OLDPWD and reassign $PWD to the new working dir.
// and go to home if no args given.

int	cd_msh(char *execve_command, char **execve_com_args, char **envp)
{
	(void) execve_command;
	(void) execve_com_args;
	(void) envp;
	ft_printf("You made it to cd_msh\n");
	table_print(execve_com_args);
	if (chdir(execve_com_args[1]))
		return (msh_error(""), -1);
	return (123);
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

int	export_msh(char *execve_command, char **execve_com_args, char **envp)
{
	(void) execve_command;
	(void) execve_com_args;
	(void) envp;
	ft_printf("You made it to export_msh\n");
	table_print(execve_com_args);
	return (0);
}

void	exit_msh(t_cominfo *cominfo, t_com_segment *com_segment)
{
	vector_free(com_segment->tokens, free_owned_token);
	msh_exit(cominfo);
}

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
