/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:46:45 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/27 14:33:40 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include "vector.h"
#include <sys/types.h>
#include <sys/wait.h>
#include "ft_printf.h"
#include "libft.h"
#include "utils.h"
#include "msh_signal.h"
#include <stdlib.h>

/*
**	msh_wait
**	
*/

int	msh_wait(t_vector *pids, int *ret_status)
{
	int	current_pid;
	int	wstatus;

	current_pid = 0;
	wstatus = 0;
	if (pids->size == 0)
		return (0);
	while (pids->size > 0)
	{
		current_pid = *((int *)pids->data);
		waitpid(current_pid, &wstatus, 0);
		vector_pop_n(pids, 0, 1);
	}
	signal_assign(SIGINT, sigint_handler_parent);
	*ret_status = WEXITSTATUS(wstatus);
	if (WIFSIGNALED(wstatus))
		*ret_status = wstatus;
	return (0);
}

/*
 *	DEBUG Function
 *
 */

int	print_execve_args(char **execve_com_args)
{
	int	i;

	i = 0;
	ft_printf("execve_com_args = [ ");
	while (execve_com_args[i])
	{
		ft_printf("%s ", execve_com_args[i]);
		i++;
	}
	ft_printf("]\n");
	return (0);
}

bool	add_item_to_com_table(t_vector *args, const char *str)
{
	char	*buf;

	buf = ft_strdup(str);
	if (!buf)
		return (1);
	if (vector_append(args, &buf))
		return (free(buf), 1);
	return (0);
}

char	**construct_execve_args(t_com_segment com_seg)
{
	t_owned_token	*token;
	t_vector		args;

	token = (t_owned_token *)com_seg.tokens->data + com_seg.start;
	vector_init(&args, sizeof(char *));
	while (token->type != T_END && token->type != T_PIPE)
	{
		if (is_redirect_type(token->type) && token->type != T_HEREDOC)
			token++;
		else if (token->type == T_STR)
		{
			if (add_item_to_com_table(&args, token->str))
				return (vector_free(&args, free_str), NULL);
		}
		token++;
	}
	if (vector_null_term(&args))
		return (vector_free(&args, free_str), NULL);
	return (vector_move_data(&args));
}
