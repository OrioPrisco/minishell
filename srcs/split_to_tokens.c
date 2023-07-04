/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_to_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:52:58 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/07/04 16:16:04 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tokens.h"

int	is_identifier_char(int i)
{
	char	c;

	c = i;
	return (c == '_' || ft_isalnum(i));
}

const char	*token_type_to_str(t_token_type token)
{
	if (token == T_SPACE)
		return ("SPACE");
	if (token == T_Q_STR)
		return ("Q_STR");
	if (token == T_DQ_STR)
		return ("T_DQ_STR");
	if (token == T_STR)
		return ("STR");
	if (token == T_END)
		return ("END");
	if (token == T_REDIRECT_STDOUT)
		return (">");
	if (token == T_REDIRECT_STDIN)
		return ("<");
	if (token == T_HEREDOC)
		return ("<<");
	if (token == T_REDIRECT_STDOUT_APPEND)
		return (">>");
	if (token == T_PIPE)
		return ("|");
	return ("UNKNOWN");
}
#include "vector.h"

//TODO : check how bash handles white space chars. a\nb acts like a;b
// error out in case of unknown character ?
static t_token	get_one_token(const char *str)
{
	if (ft_isspace(*str))
		return ((t_token){{str, ft_next_non_space(str) - str}, T_SPACE});
	else if (*str == '$')
		return ((t_token){{str,
				ft_next_non_match(str + 1, is_identifier_char) - str}, T_STR});
	else if (ft_strchr("\"\'", *str))
		return ((t_token){{str, 1 + ft_strchrnul(str + 1, *str) - str}, *str});
	else if (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "<<", 2))
		return ((t_token){{str, 2}, *(str) + 1});
	else if (ft_strchr("<>|", *str))
		return ((t_token){{str, 1}, *str});
	return ((t_token){{str, ft_strpbrknul(str, "$\'\" \t\n\v\f\r<>|") - str}, T_STR});
}

//about whitespace :
// bash treats things separated by \n as separate commands, unless quoted.
//  whoever calls this function should make sure that there are no unquoted \n
//  because i sure don't
// space and tabs are treated the same
// \v
// \f
// \r
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
