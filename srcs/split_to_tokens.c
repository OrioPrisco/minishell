/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_to_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:52:58 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/09/05 20:30:48 by OrioPrisco       ###   ########.fr       */
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
//returns the next token in a string of text
static t_token	get_one_token(const char *str)
{
	if (ft_strchr("\t ", *str))
		return ((t_token){{str, ft_strspn(str, "\t ")}, T_SPACE});
	else if (*str == '$')
		return ((t_token){{str, next_non_identifier(str) - str}, T_VAR});
	else if (ft_strchr("\"\'", *str))
		return ((t_token){{str, 1 + ft_strchrnul(str + 1, *str) - str}, *str});
	else if (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "<<", 2))
		return ((t_token){{str, 2}, *(str) + 1});
	else if (ft_strchr("<>|", *str))
		return ((t_token){{str, 1}, *str});
	else if (*str == '*')
		return ((t_token){{str, ft_strspn(str, "*")}, T_WILDCARD});
	return ((t_token){{str, ft_strcspn(str, "$\'\" \t\n\v\f\r<>|*")}, T_STR});
}

//output tokens may be nonsensical, like unterminated quote tokens
// or redirect tokens at the end of the list
//splits a string of text into tokens. will  initialize the vector
// returns 0 on success and populates the vector
// returns 1 on error and frees the vector
bool	split_to_tokens(const char *str, t_vector *vec_token)
{
	t_token		curr;

	vector_init(vec_token, sizeof(t_token));
	while (*str)
	{
		curr = get_one_token(str);
		if (vector_append(vec_token, &curr))
			return (vector_clear(vec_token), 1);
		str = curr.strview.start + curr.strview.size;
	}
	curr = (t_token){{str, 0}, T_END};
	if (vector_append(vec_token, &curr))
		return (vector_clear(vec_token), 1);
	return (0);
}

/*
#include <readline/readline.h>
#include <stdio.h>
#include "env_var.h"

int	main(int argc, char **argv, char **envp)
{
	t_vector		owned_tokens;
	size_t			i;
	t_owned_token	*token;
	char			*line;

	(void)argc;
	(void)argv;
	i = 0;
	line = readline("minishell> ");
	if (!line)
		return (1);
	if (parse_line(line, &owned_tokens, envp))
		return (free(line), 1);
	while (i < owned_tokens.size)
	{
		token = ((t_owned_token *)owned_tokens.data) + i;
		printf("%s : %s\n", token_type_to_str(token->type), token->str);
		i++;
	}
	free(line);
	vector_free(&owned_tokens, free_owned_token);
}
*/
