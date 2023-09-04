/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:14:32 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/09/05 20:35:52 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "libft.h"
#include "minishell.h"

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

static const t_tok_map_entry	g_token_map[] = {
{T_SPACE, "SPACE"},
{T_Q_START, "Q_START"},
{T_DQ_START, "DQ_START"},
{T_Q_END, "Q_END"},
{T_DQ_END, "DQ_END"},
{T_STR, "STR"},
{T_END, "END"},
{T_REDIRECT_STDOUT, ">"},
{T_REDIRECT_STDIN, "<"},
{T_HEREDOC, "<<"},
{T_REDIRECT_STDOUT_APPEND, ">>"},
{T_PIPE, "|"},
{T_VAR, "VAR"},
{T_WILDCARD, "*"},
{T_DIR_SEP, "/"},
{0, NULL},
};

const char	*token_type_to_str(t_token_type token)
{
	const t_tok_map_entry	*entry;

	entry = &g_token_map[0];
	while (entry->str)
	{
		if (entry->type == token)
			return (entry->str);
		entry++;
	}
	return ("UNKNOWN");
}

bool	is_text_type(t_token_type type)
{
	return (0
		|| type == T_STR
		|| type == T_VAR
	);
}

bool	is_redirect_type(t_token_type type)
{
	return (0
		|| type == T_REDIRECT_STDOUT
		|| type == T_REDIRECT_STDIN
		|| type == T_REDIRECT_STDOUT_APPEND
		|| type == T_HEREDOC
	);
}
