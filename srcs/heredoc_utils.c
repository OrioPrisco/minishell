/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:00:30 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/21 18:09:42 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	check_for_heredoc
**	
*/

static bool	check_for_heredoc(t_vector *tokens, int start, int stop)
{
	int				i;
	t_owned_token	*current;

	i = start;
	while (i < stop)
	{
		current = (t_owned_token *)tokens->data + i;
		if (current->type == T_HEREDOC)
			return (1);
		i++;
	}
	return (0);
}

int	check_and_open_heredoc(t_vector *tokens, int start, int stop)
{
	int			ret;

	ret = 0;
	if (check_for_heredoc(tokens, start, stop))
	{
		ft_printf("heredoc present!\n");
		(void)ret;
		// ret = open_redirects(tokens, start, stop, vec_fds);
		// if (ret)
		// 	return (close_open_redirects(vec_fds), ret);
	}
	return (0);
}
