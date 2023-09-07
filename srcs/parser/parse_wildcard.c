/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:10:24 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/09/07 21:19:04 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "wildcards.h"
#include "utils.h"
#include "vector.h"
#include "path.h"
#include <stdlib.h>
#include "utils.h"

static void	sort_wildcards(t_vector *vector)
{
	vector_sort(vector, compare_str);
}

static bool	expand_wildcard_wrapper(const t_owned_token *expr, t_vector *dest)
{
	size_t	i;
	char	*path;

	vector_init(dest, sizeof(t_owned_token));
	if (expr->type == T_DIR_SEP && expand_wildcard(expr + 1, "/", dest))
		return (vector_free(dest, free_owned_token));
	if (expr->type != T_DIR_SEP && expand_wildcard(expr, ".", dest))
		return (vector_free(dest, free_owned_token));
	if (!WILDCARD_IN_CWD)
		return (sort_wildcards(dest), 0);
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
	return (sort_wildcards(dest), 0);
}

// 0  means malloc error
// -1 means no result
int	parse_wildcard(t_vector *dest, const t_token *tok, char **envp,
		int to_merge)
{
	t_vector		wildcard_expr;
	t_vector		wildcard_result;
	size_t			i;
	t_owned_token	token;

	if (compile_wildcard_expr(tok, &wildcard_expr, envp, to_merge))
		return (0);
	if (expand_wildcard_wrapper(wildcard_expr.data, &wildcard_result))
		return (vector_free(&wildcard_expr, free_owned_token), 0);
	vector_free(&wildcard_expr, free_owned_token);
	if (!wildcard_result.size)
		return (vector_free(&wildcard_result, free_str), -2);
	i = 0;
	while (i < wildcard_result.size)
	{
		token = (t_owned_token){((char **)wildcard_result.data)[i++], T_STR};
		if (vector_append(dest, &token))
			return (vector_free(&wildcard_result, free_str), 0);
	}
	return (vector_free(&wildcard_result, free_str), to_merge);
}
