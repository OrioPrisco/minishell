/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:46:45 by dpentlan          #+#    #+#             */
/*   Updated: 2023/08/03 13:52:06 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include "vector.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "ft_printf.h"

/*
**	msh_wait
**	
*/

int	msh_wait(t_vector *pids)
{
	while (pids->size > 0)
	{
		waitpid(((long) pids->data + pids->size), NULL, 0);
		vector_pop_n(pids, pids->size, 1);
	}
	return (0);
}

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

int	add_item_to_com_table(char **execve_com_args, char *str)
{
	(void)execve_com_args;
	(void)str;
	return (0);
}

/*
**	
**	check the token logic. here I'm adding 1 if < > >> << so that we skip over 
		certain words
		CHECK THESE CASES
*/

int	construct_execve_args(t_com_segment com_seg, char **execve_com_args)
{
	int			i;
	t_vector	*tokens;

	if (!execve_com_args)
		execve_com_args = (char **)malloc(sizeof(char *) * 1);
	if (!execve_com_args)
		return (1);
	tokens = com_seg.tokens;
	i = com_seg.start;
	while (i < com_seg.stop)
	{
		if (((t_owned_token *)tokens->data + i)->type == T_STR)
			add_item_to_com_table(execve_com_args,
				((t_owned_token *)tokens->data + i)->str);
		if (((t_owned_token *)tokens->data + i)->type == T_REDIRECT_STDIN
			|| ((t_owned_token *)tokens->data + i)->type == T_REDIRECT_STDOUT
			|| ((t_owned_token *)tokens->data + i)->type == T_REDIRECT_STDOUT_APPEND
			|| ((t_owned_token *)tokens->data + i)->type == T_HEREDOC
			)
			i++;
		i++;
	}	
	return (0);
}
