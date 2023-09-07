/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:47:53 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/09/05 17:52:10 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "vector.h"
#include <stdlib.h>

// -1 means parse  error
// 0  means malloc error
int	parse_text(t_vector *dest, const t_token *tok, char **envp)
{
	t_owned_token	token;
	char			*text;
	int				to_merge;

	to_merge = seek_tokens_to_merge(tok);
	if (to_merge == -1)
		return (-1);
	if (merge_tokens(&text, tok, to_merge, envp))
		return (0);
	token = (t_owned_token){text, T_STR};
	if (vector_append(dest, &token))
		return (free(text), 0);
	return (to_merge);
}
