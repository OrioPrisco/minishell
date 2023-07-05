/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_to_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:52:58 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/07/05 16:51:18 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tokens.h"
#include "vector.h"

//about whitespace :
// bash treats things separated by \n or \r as separate commands, unless quoted.
//  whoever calls this function should make sure that there
//  are no unquoted \n or \r, because i sure don't
// space and tabs are treated as whitespace
// \v and \f are printed correctly, but do not count as whitespace
//error out in case of unknown character ?
static t_token	get_one_token(const char *str)
{
	if (ft_strchr("\t ", *str))
		return ((t_token){{str, ft_strspn(str, "\t ")}, T_SPACE});
	else if (*str == '$')
		return ((t_token){{str,
				ft_next_non_match(str + 1, is_identifier_char) - str}, T_STR});
	else if (ft_strchr("\"\'", *str))
		return ((t_token){{str, 1 + ft_strchrnul(str + 1, *str) - str}, *str});
	else if (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "<<", 2))
		return ((t_token){{str, 2}, *(str) + 1});
	else if (ft_strchr("<>|", *str))
		return ((t_token){{str, 1}, *str});
	return ((t_token){{str, ft_strcspn(str, "$\'\" \t\n\v\f\r<>|")}, T_STR});
}

//output tokens may be nonsensical, like unterminated quote tokens
// or redirect tokens at the end of the list
//ideal return type would probably be optional<t_vector>
t_token	*split_to_tokens(const char *str)
{
	t_vector	vec_token;
	t_token		curr;

	vector_init(&vec_token, sizeof(t_token));
	while (*str)
	{
		curr = get_one_token(str);
		if (vector_append(&vec_token, &curr))
			return (vector_clear(&vec_token), NULL);
		str = curr.strview.start + curr.strview.size;
	}
	curr = (t_token){{str, 0}, T_END};
	if (vector_append(&vec_token, &curr))
		return (vector_clear(&vec_token), NULL);
	return (vec_token.data);
}

/*
#include <readline/readline.h>
#include <stdio.h>

int main()
{
	t_token	*tokens;
	tokens = split_to_tokens(readline("minishell>"));
	while (tokens->type != T_END)
	{
		printf("%s : %.*s\n", token_type_to_str(tokens->type),
			(int)tokens->strview.size, tokens->strview.start);
		tokens++;
	}
}
*/
