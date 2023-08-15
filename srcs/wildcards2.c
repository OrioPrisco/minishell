/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 18:43:42 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/08/15 22:13:59 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"
#include "vector.h"
#include "utils.h"
#include "tokens.h"

void	sort_wildcards(t_vector *vector)
{
	vector_sort(vector, compare_str);
}

// vector operations are unchecked because the correct amount is
//  allocated upfront
static bool	merge_if_no_result(t_vector *result, t_vector *expr)
{
	size_t		len;
	t_token		*tok;
	t_vector	sbuilder;

	len = 0;
	tok = expr->data;
	while (tok->type != T_END)
		len += tok++->strview.size;
	if (vector_allocate(vector_init(&sbuilder, sizeof(char)), len + 1))
		return (1);
	tok = expr->data;
	while (tok->type != T_END)
	{
		vector_append_elems(&sbuilder, tok->strview.start, tok->strview.size);
		tok++;
	}
	vector_null_term(&sbuilder);
	if (vector_append(result, &sbuilder.data))
		return (vector_clear(&sbuilder));
	return (0);
}

bool	substitute_one_wildcard(t_vector *vector, size_t i)
{
	t_vector		wildcard_expr;
	t_vector		wildcard_result;
	t_owned_token	tok;

	if (compile_wildcard_expr(((t_owned_token *)vector->data + i),
			&wildcard_expr))
		return (1);
	if (expand_wildcard(wildcard_expr.data,
			&"/"[((t_token *)wildcard_expr.data)->type != T_DIR_SEP],
			vector_init(&wildcard_result, sizeof(char *)))
		|| (!wildcard_result.size
			&& merge_if_no_result(&wildcard_result, &wildcard_expr)))
		return (vector_clear(&wildcard_expr),
			vector_free(&wildcard_result, free_str), 1);
	vector_clear(&wildcard_expr);
	while (is_wildcard_expr_type((((t_owned_token *)vector->data) + i)->type)
		&& i < vector->size)
		vector_pop_n(vector, i, 1);
	tok.type = T_STR;
	while (wildcard_result.size)
		if (vector_pop(&wildcard_result, 0, &tok.str),
			vector_insert(vector, i, &tok))
			return (free_owned_token(&tok),
				vector_free(&wildcard_result, free_str), 1);
	return (vector_free(&wildcard_result, free_str), 0);
}
