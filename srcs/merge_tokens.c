/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:22:52 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/07/24 12:34:27 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "vector.h"
#include <stdlib.h>

//returns the total size of the next text tokens
// also stores the number of text tokens observed in num_strings
static size_t	text_tokens_len(const t_vector *vec_token, size_t index,
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
		if (!is_text_type(token->type))
			break ;
		size += token->strview.size;
		i++;
	}
	*num_strings = i;
	return (size + !!i);
}

//vector_append_elems are unchecked, as we have allocate enough memory
// with vector_allocate (as long as there's no bugs)
//merges tokens into a single owned_token and appends it to the output.
// does not add space tokens
static bool	merge_one_token(t_vector *dest, const t_vector *src, size_t index,
	size_t *num_strings)
{
	t_vector		sbuilder;
	size_t			i;
	t_stringview	*strview;
	t_owned_token	token;

	vector_init(&sbuilder, sizeof(char));
	if (vector_allocate(&sbuilder, text_tokens_len(src, index, num_strings)))
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
	if (vector_append(dest, &token))
		return (free(token.str), 1);
	return (0);
}

//merges tokens into owned tokens
//will initialize dest.
//on failure returns 1 and clears dest
//on success returns 0 and dest will contain the result
bool	merge_tokens(t_vector *dest, const t_vector *src)
{
	size_t			index;
	size_t			num_strings;

	vector_init(dest, sizeof(t_owned_token));
	index = 0;
	while (index < src->size)
	{
		if (merge_one_token(dest, src, index, &num_strings))
			return (vector_free(dest, free_owned_token), 1);
		index += num_strings + (!num_strings);
	}
	return (0);
}
