/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:58:47 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/26 14:33:16 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	access_error_print(const char *exec_name)
{
	int	ret;

	if (ft_strchr(exec_name, '/'))
	{
		ret = is_directory(exec_name);
		if (ret == 1)
			ft_dprintf(2, "%s: Is a directory\n", exec_name);
		else if (ret == -1)
			msh_error(exec_name);
		else if (access(exec_name, F_OK | X_OK))
			msh_error(exec_name);
	}
	else
		ft_dprintf(2, "%s: command not found\n", exec_name);
}
