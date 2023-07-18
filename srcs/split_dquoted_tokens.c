/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_dquoted_tokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:31:29 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/07/14 17:00:55 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "vector.h"
#include "libft.h"

//returns the next string or variable token in a dquoted string
static t_token	next_sub_token(const char *str)
{
	if (*str == '$')
		return ((t_token){{str, next_non_identifier(str) - str}, T_VAR});
	return ((t_token){{str, ft_strcspn(str, "$")}, T_STR});
}

//splits a single dquoted token into string and variables tokens
// returns 0 on success
// returns 1 on error
static bool	split_dqtoken(t_vector *dest, const t_stringview *strview)
{
	t_token	curr;
	size_t	i;

	i = 0;
	while (i < strview->size)
	{
		curr = next_sub_token(strview->start + i);
		if (curr.strview.size + i > strview->size)
			curr.strview.size = strview->size - i;
		if (vector_append(dest, &curr))
			return (1);
		i += curr.strview.size;
	}
	return (0);
}

//could probably pop and insert elemnts in place
// would require some index variables and would be harder,
// but use less memory
//splits all the dquoted tokens into strings and variables
// returns 0 on success
// returns 1 on error
bool	split_dquoted_tokens(t_vector *vec_token)
{
	t_vector	vec2;
	size_t		i;
	t_token		*token;

	vector_init(&vec2, sizeof(t_token));
	if (vector_allocate(&vec2, vec_token->size))
		return (1);
	i = 0;
	while (i < vec_token->size)
	{
		token = ((t_token *)vec_token->data) + i;
		if (!(token->type == T_DQ_STR))
		{
			if (vector_append(&vec2, token))
				return (vector_clear(&vec2), 1);
		}
		else if (split_dqtoken(&vec2, &token->strview))
			return (vector_clear(&vec2), 1);
		i++;
	}
	return (vector_move(vec_token, &vec2), 0);
}
