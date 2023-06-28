/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_to_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:52:58 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/06/28 17:55:47 by OrioPrisco       ###   ########.fr       */
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

//about whitespace :
// bash treates things separates by \n as separate commands, unless quoted.
//  whoever calls this function should make sure that there are no unquoted \n
//  because i sure don't
// space and tabs are treated the same
// \v
// \f
// \r
t_token	*split_to_tokens(const char *str)
{
	t_token	*output;
	size_t	i;
	char	*end_token;

	output = ft_calloc(sizeof(*output), 100); // TODO : do not hardcode output size. Use vector ? also check malloc error
	i = 0;
	while (*str)
	{
		if (ft_isspace(*str)) //TODO : check how bash handles white space chars. a\nb acts like a;b
		{
			output[i++] = (t_token){NULL, T_SPACE};
			str = ft_next_non_space(str);
		}
		else if (*str == '$')
		{
			end_token = ft_next_non_match(str + 1, is_identifier_char);
			output[i++] = (t_token){ft_substr(str, 0, end_token - str), T_STR}; // TODO : check malloc error
			str = end_token;
		}
		else if (ft_strchr("\"\'", *str))
		{
			end_token = ft_strchrnul(str + 1, *str) - 1;
			output[i++] = (t_token){ft_substr(str, 1, end_token - str), *str}; // TODO : check malloc error
			str = end_token + 2;// check for unterminated quote / dquote
		}
		else
		{
			end_token = ft_strpbrknul(str, "$\'\" \t\n\v\f\r");
			output[i++] = (t_token){ft_substr(str, 0, end_token - str), T_STR}; // TODO : check malloc error
			str = end_token;
		}
		// handle >> / <<
		// handle > / <
		// handle |
		// errour out in case of unknown character
	}
	output[i] = (t_token){NULL, T_END};
	return (output);
}

/*
#include <readline/readline.h>
#include "ft_printf.h"

int main()
{
	t_token	*tokens;
	tokens = split_to_tokens(readline("minishell>"));
	while (tokens->type != T_END)
	{
		ft_printf("token : %c, str : %s\n",
			tokens->type, tokens->opt_str?tokens->opt_str:"(null)");
		tokens++;
	}
}
*/
