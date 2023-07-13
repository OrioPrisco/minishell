/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:17:16 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/07/13 16:22:32 by OrioPrisco       ###   ########.fr       */
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

//returns a pointer to the next token that is not a space
//or to the end token
static t_token	*next_token(const t_token *token)
{
	while (token->type != T_END)
	{
		token++;
		if (token->type != T_SPACE)
			return ((t_token *)token);
	}
	return ((t_token *)token);
}

//checks that every redirect has a text token afterward
//also changes the type of text tokens after a heredoc to T_STR
// to prevent expansion
//returns 0 on success
//returns 1 if a redirect has no text token afterward
bool	process_redirects(t_vector *vec_token)
{
	t_token	*token;
	t_token	*next;

	token = vec_token->data;
	while (token->type != T_END)
	{
		if (is_redirect_type(token->type))
		{
			next = next_token(token);
			if (!is_text_type(next->type))
			{
				ft_putstr_fd("Parsing error near ", 2);
				ft_putstr_fd(token_type_to_str(token->type), 2);
				ft_putstr_fd("\n", 2);
				return (1);
			}
			if (token->type == T_HEREDOC)
				while (is_text_type(next->type))
					next++->type = T_STR;
			token = next;
		}
		token++;
	}
	return (0);
}
