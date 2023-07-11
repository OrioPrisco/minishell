/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:22:52 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/07/11 19:42:52 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "vector.h"
#include <stdlib.h>

static size_t	tokens_len(const t_vector *vec_token, size_t index,
	size_t *num_strings)
{
	size_t	size;
	size_t	i;
	t_token	*token;

	size = 0;
	i = 0;
	while (i + index < vec_token->size)
	{
		token = ((t_token *)vec_token->data) + index + i;
		if (!(token->type == T_STR || token->type == T_Q_STR
				|| token->type == T_VAR))
			break ;
		size += token->strview.size;
		i++;
	}
	*num_strings = i;
	return (size + !!i);
}

//vector_append_elems are unchecked, as we have allocate enough memory
// with vector_allocate (as long as there's no bugs)
static bool	merge_one_token(t_vector *dest, const t_vector *src, size_t index,
	size_t *num_strings)
{
	t_vector		sbuilder;
	size_t			i;
	t_stringview	*strview;
	t_owned_token	token;

	vector_init(&sbuilder, sizeof(char));
	if (vector_allocate(&sbuilder, tokens_len(src, index, num_strings)))
		return (1);
	i = index;
	while (i < index + *num_strings)
	{
		strview = &(((t_token *)src->data)[i++].strview);
		vector_append_elems(&sbuilder, strview->start, strview->size);
	}
	if (*num_strings)
		vector_null_term(&sbuilder);
	token = (t_owned_token){vector_move_data(&sbuilder), T_STR};
	if (!*num_strings)
		token.type = ((t_token *)src->data)[i++].type;
	if (token.type != T_SPACE && vector_append(dest, &token))
		return (free(token.str), 1);
	return (0);
}

bool	merge_tokens(t_vector *dest, const t_vector *src)
{
	size_t			index;
	size_t			num_strings;

	vector_init(dest, sizeof(t_owned_token));
	index = 0;
	while (index < src->size)
	{
		if (merge_one_token(dest, src, index, &num_strings))
			return (vector_clear(dest), 1);
		index += num_strings + (!num_strings);
	}
	return (0);
}
