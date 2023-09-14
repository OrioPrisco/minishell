/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 09:08:51 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/14 14:13:22 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "tokens.h"
#include "filedescriptors.h"
#include "minishell.h"
#include "ft_printf.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static bool	check_for_redirects(t_vector *tokens, int start, int stop)
{
	int				i;
	t_owned_token	*current;

	i = start;
	while (i < stop)
	{
		current = (t_owned_token *)tokens->data + i;
		if (current->type == T_REDIRECT_STDOUT
			|| current->type == T_REDIRECT_STDOUT_APPEND
			|| current->type == T_REDIRECT_STDIN)
			return (1);
		i++;
	}
	return (0);
}

/*
**	check_and_open_redirects
**	
*/

int	check_and_open_redirects(t_vector *tokens, t_vector *vec_fds,
							int start, int stop)
{
	int			ret;

	ret = 0;
	if (check_for_redirects(tokens, start, stop))
	{
		ret = open_redirects(tokens, start, stop, vec_fds);
		if (ret)
			return (vector_free(vec_fds, free_fds), ret);
	}
	return (0);
}

/*	
**	recursive function for crawling the abstract syntax tree.
**	
**	WORK IN PROGRESS. Initial version of this function is just for testing
**	interface with fd handler functions
**	this should call single command with token address of where to start
**	and the number of tokens to look through (adjust based on presence of 
**	&& || or T_END)
**/

int	tree_crawler(t_vector *tokens, t_cominfo *cominfo)
{
	t_vector	pids;

	vector_init(&pids, sizeof(int));
	if (fork_loop(tokens, cominfo, &pids))
		return (msh_wait(&pids), vector_clear(&pids), -1);
	return (msh_wait(&pids), vector_clear(&pids), 0);
}
