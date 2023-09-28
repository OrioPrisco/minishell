/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:58:47 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/28 14:09:21 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "minishell.h"
#include "vector.h"
#include "libft.h"
#include <stdio.h>
#include "utils.h"
#include "env_var.h"
#include "tokens.h"
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include "path.h"
#include "ft_printf.h"
#include <errno.h>

void	msh_error(const char *message)
{
	ft_putstr_fd("minishell: ", 2);
	perror(message);
}

void	msh_exit(t_cominfo *cominfo, int ret_code, int save_his)
{
	rl_clear_history();
	if (save_his)
	{
		if (isatty(STDIN_FILENO))
			ft_putstr_fd("exit\n", 1);
		save_history(cominfo->env_ret, &cominfo->com_list);
	}
	if (cominfo->tokens)
		vector_free(cominfo->tokens, free_owned_token);
	vector_free(&cominfo->com_list, free_str);
	vector_free(&cominfo->env_ret->env_vec, free_str);
	exit(ret_code);
}

void	redirect_error_print(const char *filename)
{
	int	ret;

	ret = is_directory(filename);
	if (ret == 1)
	{
		errno = EISDIR;
		msh_error(filename);
	}
	else if (ret == -1)
		msh_error(filename);
	else if (access(filename, F_OK))
		msh_error(filename);
}

// Change prev_ret to new previous return in structure.

void	set_err_code(t_cominfo *cominfo, int err_code)
{
	cominfo->env_ret->prev_ret = err_code;
}

void	access_error_print(const char *exec_name, t_cominfo *cominfo)
{
	int			ret;
	const char	*path;

	path = get_env_var(cominfo->env_ret, "PATH", 4);
	if (ft_strchr(exec_name, '/') || !path || !*path)
	{
		ret = is_directory(exec_name);
		if (ret == 1)
		{
			errno = EISDIR;
			return (msh_error(exec_name), set_err_code(cominfo, 126));
		}
		else if (ret == -1)
			return (msh_error(exec_name), set_err_code(cominfo, 127));
		else if (access(exec_name, F_OK | X_OK))
			return (msh_error(exec_name), set_err_code(cominfo, 126));
	}
	else
	{
		ft_dprintf(2, "%s: command not found\n", exec_name);
		cominfo->env_ret->prev_ret = 127;
	}
}
