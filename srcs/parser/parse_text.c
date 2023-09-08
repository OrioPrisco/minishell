/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:47:53 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/09/08 14:47:56 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "vector.h"
#include <stdlib.h>

bool	is_wildcard_expr(const t_token	*tok, int to_merge)
{
	while (to_merge--)
	{
		if (tok++->type == T_WILDCARD)
			return (1);
	}
	return (0);
}

// -1 means parse  error
// 0  means malloc error
int	parse_text(t_vector *dest, const t_token *tok,
		const t_env_ret *env_ret)
{
	t_owned_token	token;
	char			*text;
	int				to_merge;
	int				ret;

	to_merge = seek_tokens_to_merge(tok);
	if (to_merge == -1)
		return (-1);
	if (is_wildcard_expr(tok, to_merge))
	{
		ret = parse_wildcard(dest, tok, env_ret, to_merge);
		if (ret == 0)
			return (0);
		if (ret != -1)
			return (ret);
	}
	if (merge_tokens(&text, tok, to_merge, env_ret))
		return (0);
	token = (t_owned_token){text, T_STR};
	if (vector_append(dest, &token))
		return (free(text), 0);
	return (to_merge);
}
