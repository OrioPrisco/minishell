/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:14:32 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/07/18 13:59:09 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "libft.h"
#include "minishell.h"

void	print_tokens(t_vector *owned_tokens)
{
	size_t			i;
	t_owned_token	*token;

	i = 0;
	while (i < owned_tokens->size)
	{
		token = ((t_owned_token *)owned_tokens->data) + i;
		printf("%s : %s\n", token_type_to_str(token->type), token->str);
		i++;
	}
}

//returns whether a character is alphanumeric or _
//careful, identifier cannot start with a digit.
//use next_non_indetifier to check entire strings
int	is_identifier_char(int i)
{
	char	c;

	c = i;
	return (c == '_' || ft_isalnum(i));
}

//returns a pointer to first character that is not
// part of a valid identifier
//the string may start with $, which will be skipped
//the return pointer may point to the terminating nul byte if
//the entire string is a valid identifier
//handles the special case $?
char	*next_non_identifier(const char *str)
{
	if (!ft_strncmp(str, "$?", 2))
		return ((char *)str + 2);
	if (*str == '$')
		str++;
	if (!(ft_isalpha(*str) || *str == '_'))
		return ((char *)str);
	str++;
	while (*str && is_identifier_char(*str))
		str++;
	return ((char *)str);
}

const char	*token_type_to_str(t_token_type token)
{
	if (token == T_SPACE)
		return ("SPACE");
	if (token == T_Q_STR)
		return ("Q_STR");
	if (token == T_DQ_STR)
		return ("DQ_STR");
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
	if (token == T_VAR)
		return ("VAR");
	return ("UNKNOWN");
}

void	free_owned_tokens(t_vector *owned_tokens)
{
	size_t			i;
	t_owned_token	*current;

	i = 0;
	while (i < owned_tokens->size)
	{
		current = (t_owned_token *)owned_tokens->data + i;
		free(current->str);
		i++;
	}
}
