/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:29:42 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/08/09 16:46:33 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "vector.h"
#include "libft.h"

static bool	split_str_token(const char *str, t_vector *dest)
{
	t_token	token;

	while (*str)
	{
		if (*str == '/')
			token = (t_token){{str, 1}, T_DIR_SEP};
		else
			token = (t_token){{str, ft_strcspn(str, "/")}, T_STR};
		if (vector_append(dest, &token))
			return (1);
		str = token.strview.start + token.strview.size;
	}
	return (0);
}
// compiles owned tokens to a wildcard expression
// on success returns 0 and the vector will be initialized and filled
// on failre returns 1 and the vector will be cleared

bool	compile_wildcard_expr(const t_owned_token *src, t_vector *dest)
{
	t_token		token;

	vector_init(dest, sizeof(t_token));
	while (is_wildcard_expr_type(src->type))
	{
		if (src->type == T_WILDCARD)
		{
			token = (t_token){{"*", 1}, T_WILDCARD};
			if (vector_append(dest, &token))
				return (vector_clear(dest), 1);
		}
		else if (is_text_type(src->type))
			if (split_str_token(src->str, dest))
				return (vector_clear(dest), 1);
	}
	token = (t_token){{NULL, 0}, T_END};
	if (vector_append(dest, &token))
		return (vector_clear(dest), 1);
	return (0);
}

//filename is full filename, while curr is what is left to match
bool	match_subexpression(const t_token *token, const char *filename,
			const char *curr)
{
	if (token->type == T_END || token->type == T_DIR_SEP)
		return (!*curr);
	if (is_text_type(token->type))
	{
		if (!ft_strncmp(curr, token->strview.start, token->strview.size))
			return (match_subexpression
				(token + 1, filename, curr + token->strview.size));
		return (0);
	}
	if (token->type != T_WILDCARD
		|| (*filename == '.' && filename == curr))
		return (0);
	while (*curr)
		if (match_subexpression(token + 1, filename, curr++))
			return (1);
	return (0);
}
