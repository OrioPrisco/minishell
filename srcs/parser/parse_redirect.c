/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:07:23 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/09/28 17:22:21 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "vector.h"
#include "ft_printf.h"
#include <stdlib.h>
#include "parser_int.h"

static const t_token	*next_tok(const t_token *tok)
{
	if (tok[1].type == T_SPACE)
		return (tok +2);
	return (tok + 1);
}

int	parse_hd(t_vector *dest, const t_token *tok,
		t_rlinfo_com rlinfo_com)
{
	t_owned_token	token;
	int				to_merge;
	char			*hd_sep;
	int				ret;

	to_merge = seek_tokens_to_merge(tok + 1);
	if (to_merge == -1)
		return (-1);
	if (merge_tokens(&hd_sep, tok + 1, to_merge, NULL))
		return (0);
	ret = open_heredoc(hd_sep, rlinfo_com);
	free(hd_sep);
	if (ret < 0)
		return (ret + 1);
	token = (t_owned_token){NULL, T_HEREDOC, ret};
	if (vector_append(dest, &token))
		return (0);
	return (to_merge + 1);
}

// will need to take hd_line
// -1 means parse  error
// 0  means malloc error
// could possibly put the filename in the redir token here
int	parse_redirect(t_vector *dest, const t_token *tok,
		t_rlinfo_com rlinfo_com)
{
	t_owned_token	token;
	const t_token	*next;
	int				ret;

	token = (t_owned_token){NULL, tok->type, 0};
	next = next_tok(tok);
	if (!is_textexpr_type(next->type))
		return (ft_dprintf(2, "Parse error near %s\n",
				token_type_to_str(next->type)), -1);
	if (tok->type == T_HEREDOC)
		return (parse_hd(dest, tok, rlinfo_com));
	if (vector_append(dest, &token))
		return (0);
	ret = parse_text(dest, tok + 1, rlinfo_com.env_ret, 1);
	if (ret == 0 || ret == -1)
		return (ret);
	return (ret + 1);
}
