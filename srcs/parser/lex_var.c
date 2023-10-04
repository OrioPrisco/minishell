/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:39:10 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/10/04 12:25:02 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_int.h"
#include "libft.h"
#include "vector.h"

t_token	get_one_token_var(const char *var, t_state state)
{
	if (state == N && *var == '*')
		return ((t_token){{var, ft_strspn(var, "*")}, T_WILDCARD});
	if (*var == '/')
		return ((t_token){{var, 1}, T_DIR_SEP});
	if (state != DQ && ft_strchr(" \t", *var))
		return ((t_token){{var, ft_strspn(var, "\t ")}, T_SPACE});
	if (state != DQ)
		return ((t_token){{var, ft_strcspn(var, "\t */")}, T_STR});
	return ((t_token){{var, ft_strcspn(var, "/")}, T_STR});
}

// NULL str means var expanded to nothing
bool	split_var_to_tokens(const char *var, t_vector *dest, t_state state)
{
	t_token	curr;

	if (!var || !*var)
	{
		curr = (t_token){{"", 0}, T_VAR};
		return (vector_append(dest, &curr));
	}
	while (*var)
	{
		curr = get_one_token_var(var, state);
		if (vector_append(dest, &curr))
			return (1);
		var = curr.strview.start + curr.strview.size;
	}
	return (0);
}
