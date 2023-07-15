/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:17:16 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/07/07 16:12:30 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "tokens.h"
#include "libft.h"

//validates that all quoted tokens are terminated
// and strips the beginning and terminating ones from the stringviews
//returns 1 if a quote/dquote is unterminqted
// otherwise returns 0 and strips the beginning and terminating one
//makes the reasonable assumption that a quoted/dquoted token has at least
// length 1 (since it still contains the quotes/dquotes)
bool	process_quotes(t_vector *vec_token)
{
	size_t	i;
	t_token	*token;

	i = 0;
	while (i < vec_token->size)
	{
		token = ((t_token *)vec_token->data) + i;
		i++;
		if (!(token->type == T_DQ_STR || token->type == T_Q_STR))
			continue ;
		if (*token->strview.start
			!= *(token->strview.start + token->strview.size - 1))
			return (ft_putstr_fd("Error : unterminated quote/dquote.\n", 2), 1);
		token->strview.start++;
		token->strview.size -= 2;
	}
	return (0);
}
