/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:39:33 by dpentlan          #+#    #+#             */
/*   Updated: 2023/10/04 17:24:04 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "ft_printf.h"
#include "utils.h"
#include "error.h"
#include "env_var.h"
#include "ft_readline.h"
#include "tokens.h"

int	unset_msh(char *execve_command, char **execve_com_args, t_vector *env_vec)
{
	size_t	str_len;
	int		i;

	(void) execve_command;
	i = 1;
	while (execve_com_args[i])
	{
		str_len = ft_strlen(execve_com_args[i]);
		if (!str_len)
		{
			i++;
			continue ;
		}
		execve_com_args[i][str_len] = '=';
		del_from_env_vec(env_vec,
			check_env_vec_dup(env_vec, execve_com_args[i], str_len));
		execve_com_args[i][str_len] = 0;
		i++;
	}
	return (0);
}

int	env_msh(char *execve_command, char **execve_com_args, t_vector *env_vec)
{
	(void) execve_command;
	(void) execve_com_args;
	print_env_vec(env_vec, "");
	return (0);
}

int	exit_msh(t_cominfo *cominfo, char **execve_com_args, int save_hist)
{
	char	*ptr;
	long	num;

	if (!execve_com_args[1])
	{
		table_free(execve_com_args);
		msh_exit(cominfo,
			cominfo->env_ret->prev_ret, save_hist);
	}
	num = ft_strtol(execve_com_args[1], &ptr, 10);
	if (*ptr != '\0' || !ft_strtol_check_long(execve_com_args[1], ptr, num))
	{
		ft_dprintf(2, "minishell: exit: %s: numeric argument required\n",
			execve_com_args[1]);
		table_free(execve_com_args);
		msh_exit(cominfo, 2, save_hist);
	}
	if (execve_com_args[1] && execve_com_args[2])
	{
		ft_dprintf(2, "minishell: exit: too many arguments\n");
		return (1);
	}
	table_free(execve_com_args);
	msh_exit(cominfo, num, save_hist);
	return (0);
}

void	builtins_cleanup(t_cominfo *cominfo, t_com_segment *com_seg, int ret)
{
	vector_free(com_seg->tokens, free_owned_token);
	vector_free(&cominfo->env_ret->env_vec, free_str);
	ft_rl_clear(cominfo->rlinfo);
	msh_exit(cominfo, ret, 0);
}
