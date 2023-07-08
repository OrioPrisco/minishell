/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 09:08:51 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/08 12:44:12 by dpentlan         ###   ########.fr       */
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
	int			ret;
	t_fds		test;

	ret = 0;
	vector_init(&vec_fds, sizeof(t_fds));
	if (check_for_redirects(tokens, size))
	{
		ret = open_redirects(tokens, size, &vec_fds);
		if (ret)
			return (close_open_redirects(&vec_fds), ret);
	}
	ft_bzero((void *)&test, sizeof(test));
	open_trunc(&test, "new_file", 0);
	ft_printf("X fd: %d, fn: %s, fd_cloexec: %d\n",
		test.fd, test.fn, test.fd_cloexec);
	vector_append(&vec_fds, (void *)&test);
	ft_printf("after opens\n");
	print_open_redirects(vec_fds.data, vec_fds.size);
	close_open_redirects(&vec_fds);
	ft_printf("after close\n");
	print_open_redirects(vec_fds.data, vec_fds.size);
	close(test.fd);
	free(test.fn);
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
