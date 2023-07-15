/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 09:08:51 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/15 11:21:17 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_for_redirects(t_vector *tokens, int size)
{
	int				i;
	t_owned_token	*current;

	i = 0;
	while (i < size)
	{
		current = (t_owned_token *)tokens->data + i;
		if (current->type == T_REDIRECT_STDOUT 
			|| current->type == T_REDIRECT_STDOUT_APPEND)
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

int	single_command(t_vector *tokens, int size)
{
	t_vector	vec_fds;
	int			ret;

	ret = 0;
	vector_init(&vec_fds, sizeof(t_fds));
	if (check_for_redirects(tokens, size))
	{
		ret = open_redirects(tokens, size, &vec_fds);
		if (ret)
			return (close_open_redirects(&vec_fds), ret);
	}
	print_open_redirects((t_fds *)vec_fds.data, vec_fds.size);
	close_open_redirects(&vec_fds);
	vector_clear(&vec_fds);
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

int	tree_crawler(t_vector *tokens)
{
	int	i;
	int	ret;

	i = 0;
	while (((t_owned_token *)tokens->data + i)->type != T_END)
		i++;
	ret = single_command(tokens, i);
	return (ret);
}
