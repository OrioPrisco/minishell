/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:00:30 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/30 16:54:17 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include "vector.h"
#include "ft_printf.h"
#include <stdio.h>

/*
**	check_for_heredoc
**	
*/

static int	check_for_heredoc(t_vector *tokens, int start, int stop)
{
	int				i;
	t_owned_token	*current;

	i = start;
	while (i < stop)
	{
		current = (t_owned_token *)tokens->data + i;
		if (current->type == T_HEREDOC)
			return (i);
		i++;
	}
	return (0);
}

// placed under (void)ret;
		// ret = open_redirects(tokens, start, stop, vec_fds);
		// if (ret)
		// 	return (close_open_redirects(vec_fds), ret);

int	check_and_open_heredoc(t_vector *tokens, int start, int stop)
{
	int			ret;
	char		*limiter;

	ret = 0;
	limiter = 0;
	ret = check_for_heredoc(tokens, start, stop);
	if (ret)
	{
		limiter = ((t_owned_token *)tokens->data + (ret + 1))->str;
		ft_printf("Limiter is %s\n", limiter);
	}
	return (0);
}
