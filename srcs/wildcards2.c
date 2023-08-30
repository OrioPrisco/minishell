/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 18:43:42 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/08/30 11:59:21 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"
#include "vector.h"
#include "utils.h"
#include "tokens.h"
#include "path.h"
#include <stdlib.h>

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

// calls expand_wildcard with correct arguments,
// sorts the result and optionally remove elements not in cwd
// returns are the same as expand_wildcard
static bool	expand_wildcard_wrapper(const t_token *expr, const char *cwd,
				t_vector *dest)
{
	size_t	i;
	char	*path;

	if (expr->type == T_DIR_SEP && expand_wildcard(expr + 1, "/", dest))
		return (1);
	if (expr->type != T_DIR_SEP && expand_wildcard(expr, cwd, dest))
		return (1);
	sort_wildcards(dest);
	if (!WILDCARD_IN_CWD)
		return (0);
	i = 0;
	while (i < dest->size)
	{
		path = ((char **)dest->data)[i];
		if (!is_in_cwd(path))
		{
			free(path);
			vector_pop_n(dest, i, 1);
		}
		else
			i++;
	}
	return (0);
}

static bool	substitute_one_wildcard(t_vector *vector, size_t i)
{
	t_vector		wildcard_expr;
	t_vector		wildcard_result;
	t_owned_token	tok;

	if (compile_wildcard_expr(((t_owned_token *)vector->data + i),
			&wildcard_expr))
		return (1);
	vector_init(&wildcard_result, sizeof(char *));
	if (expand_wildcard_wrapper(wildcard_expr.data, "", &wildcard_result)
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

// finds and substitutes all wildcards expressions in the vector
// returns 0 on sucess
// returns 1 on error, and does not clear the vector
bool	substitute_all_wildcards(t_vector *vector)
{
	size_t			i;
	size_t			j;
	t_owned_token	*tok;

	i = 0;
	j = 0;
	while (i < vector->size)
	{
		tok = ((t_owned_token *)vector->data) + i;
		if (tok->type == T_WILDCARD)
		{
			if (substitute_one_wildcard(vector, j))
				return (1);
			i = j;
		}
		else if (tok->type == T_SPACE)
			j = ++i;
		else
			i++;
	}
	return (0);
}
