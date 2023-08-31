/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:17:16 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/09/05 20:30:58 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "tokens.h"
#include "libft.h"

//validates that a quoted tokens is terminated
// and strips the beginning and terminating ones from the stringview
//returns 1 if a quote/dquote is unterminated
// otherwise returns 0 and strips the beginning and terminating one
//makes the reasonable assumption that a quoted/dquoted token has at least
// length 1 (since it still contains the quotes/dquotes)
bool	process_quote(t_token *token)
{
	if (*token->strview.start
		!= *(token->strview.start + token->strview.size - 1))
	{
		ft_putstr_fd("Error : unterminated ", 2);
		if (token->type == T_Q_STR)
			ft_putstr_fd("quote.\n", 2);
		else
			ft_putstr_fd("double quote.\n", 2);
		return (1);
	}
	token->strview.start++;
	token->strview.size -= 2;
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
bool	process_redirect(t_token *token)
{
	t_token	*next;

	next = next_token(token);
	if (!is_text_type(next->type))
	{
		ft_putstr_fd("Parsing error near ", 2);
		ft_putstr_fd(token_type_to_str(token->type), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	if (token->type == T_HEREDOC)
	{
		while (is_text_type(next->type) || next->type == T_WILDCARD)
		{
			process_one_token(next);
			next++->type = T_STR;
		}
	}
	return (0);
}

//checks that a pipe is not followed by end or another pipe
bool	validate_pipe(const t_token *token)
{
	token = next_token(token);
	if (token->type == T_PIPE || token->type == T_END)
	{
		ft_putstr_fd("Unexpected Token ", 2);
		if (token->type == T_PIPE)
			ft_putstr_fd("|\n", 2);
		else
			ft_putstr_fd("\\n\n", 2);
		return (1);
	}
	return (0);
}

// processes one token by calling the relevant function
// or does nothing
bool	process_one_token(t_token	*token)
{
	if (is_redirect_type(token->type))
		return (process_redirect(token));
	if (token->type == T_PIPE)
		return (validate_pipe(token));
	if (token->type == T_Q_STR || token->type == T_DQ_STR)
		return (process_quote(token));
	return (0);
}
