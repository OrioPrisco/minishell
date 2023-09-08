/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:07:23 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/09/08 14:47:25 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "vector.h"
#include "ft_printf.h"
#include <stdlib.h>

static const t_token	*next_tok(const t_token *tok)
{
	if (tok[1].type == T_SPACE)
		return (tok +2);
	return (tok + 1);
}

// will need to take hd_line
// -1 means parse  error
// 0  means malloc error
int	parse_redirect(t_vector *dest, const t_token *tok,
		const t_env_ret *env_ret)
{
	t_owned_token	token;
	int				to_merge;
	const t_token	*next;
	char			*hd_sep;

	token = (t_owned_token){NULL, tok->type};
	next = next_tok(tok);
	if (!is_textexpr_type(next->type))
		return (ft_dprintf(2, "Parse error near %s\n",
				token_type_to_str(next->type)), -1);
	// could possibly put the filename in the redir token here
	if (vector_append(dest, &token))
		return (0);
	if (tok->type != T_HEREDOC)
		return (1);
	to_merge = seek_tokens_to_merge(tok);
	if (to_merge == -1)
		return (-1);
	if (merge_tokens(&hd_sep, tok, to_merge, env_ret))
		return (0);
	token = ((t_owned_token){hd_sep, T_STR});
	//TODO  call the heredoc function here instead of pushing a token
	if (vector_append(dest, &token))
		return (free(hd_sep), 0);
	return (to_merge + 1);
}
