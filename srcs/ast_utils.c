/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 09:08:51 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/07 13:52:10 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	
**	tokens is pointer to token space
**	size is the number of tokens to look through
**	return could be return status of command?
**/

int	single_command(t_token *tokens, int size)
{
	t_vector	vec_fds;
	t_fds		*fds;

	vector_init(&vec_fds, sizeof(t_fds));
	fds = open_redirects(tokens, size, &vec_fds);
	if (!fds)
		ft_printf("either no files opened, or error opening...\n");
	free(fds);
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

	i = 0;
	while (tokens[i].type != T_END)
		i++;
	single_command(tokens, i);
	return (0);
}
