/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 09:08:51 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/21 18:04:23 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_for_redirects(t_vector *tokens, int start, int stop)
{
	int				i;
	t_owned_token	*current;

	i = start;
	while (i < stop)
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
			return (close_open_redirects(vec_fds), ret);
	}
	return (0);
}

/*
**	func_name
**	
*/

void	cleanup_redirects(t_vector *vec_fds)
{
	close_open_redirects(vec_fds);
	vector_clear(vec_fds);
}

/*	
**	tokens is pointer to token space
**	return could be return status of command?
**	print_relavent_tokens(tokens, start, stop);
**	print_open_redirects((t_fds *)vec_fds.data, vec_fds.size);
**/

int	single_command(t_vector *tokens, int start, int stop)
{
	t_vector	vec_fds;
	int			ret;

	ret = 0;
	vector_init(&vec_fds, sizeof(t_fds));
	ret = check_and_open_heredoc(tokens, start, stop);
	if (ret)
		return (ret);
	ret = check_and_open_redirects(tokens, &vec_fds, start, stop);
	if (ret)
		return (ret);
	cleanup_redirects(&vec_fds);
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
	ret = pipe_loop(tokens, i);
	return (ret);
}
