/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:15:56 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/09/27 14:53:36 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "ft_printf.h"
#include "vector.h"
#include "parser_int.h"

// -1 means parse error
// 0 means malloc error
int	parse_pipe(t_vector *dest, const t_token *tok)
{
	t_owned_token	token;

	if (dest->size == 0 || tok[1].type == T_PIPE
		|| (tok[1].type == T_SPACE && tok[2].type == T_PIPE))
		return (ft_dprintf(2, "Parse error near |\n"), -1);
	token = (t_owned_token){NULL, T_PIPE, 0};
	if (tok[1].type == T_END
		|| (tok[1].type == T_SPACE && tok[2].type == T_END))
		return (ft_dprintf(2, "Parse error near \\n\n"), -1);
	if (vector_append(dest, &token))
		return (0);
	return (1);
}
