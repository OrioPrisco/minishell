/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 09:08:51 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/08 09:18:29 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_for_redirects(t_token *tokens, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (tokens[i].type == T_REDIRECT_STDOUT
			|| tokens[i].type == T_REDIRECT_STDOUT_APPEND)
			return (1);
		i++;
	}
	return (0);
}

/*	
**	tokens is pointer to token space
**	size is the number of tokens to look through
**	return could be return status of command?
**/

int	single_command(t_token *tokens, int size)
{
	t_vector	vec_fds;
	t_fds		*fds;
	int			ret;

	fds = 0;
	ret = 0;
	vector_init(&vec_fds, sizeof(t_fds));
	if (check_for_redirects(tokens, size))
	{
		ret = open_redirects(tokens, size, &vec_fds);
		fds = vec_fds.data;
		if (ret)
			return (close_open_redirects(fds, vec_fds.size),
				ret);
	}
	print_open_redirects(fds, vec_fds.size);
	close_open_redirects(fds, vec_fds.size);
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

int	tree_crawler(t_token *tokens)
{
	int	i;
	int	ret;

	i = 0;
	while (tokens[i].type != T_END)
		i++;
	ret = single_command(tokens, i);
	return (ret);
}
