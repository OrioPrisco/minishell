/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:52:58 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/09/18 13:14:53 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tokens.h"
#include "vector.h"
#include "ft_readline.h"
#include "parser_int.h"

typedef enum e_state
{
	NORMAL,
	QUOTE,
	DQUOTE,
	N = NORMAL,
	Q = QUOTE,
	DQ = DQUOTE,
}	t_state;

//about whitespace :
// bash treats things separated by \n or \r as separate commands, unless quoted.
//  whoever calls this function should make sure that there
//  are no unquoted \n or \r, because i sure don't
// space and tabs are treated as whitespace
// \v and \f are printed correctly, but do not count as whitespace
//error out in case of unknown character ?
static	t_token	get_one_token_cont(t_state	*state, const char *str)
{
	if (*str == '/')
		return ((t_token){{str, 1}, T_DIR_SEP});
	if (*state == DQUOTE)
		return ((t_token){{str, ft_strcspn(str, "$\"/")}, T_STR});
	if (*state == QUOTE)
		return ((t_token){{str, ft_strcspn(str, "\'/")}, T_STR});
	return ((t_token){{str, ft_strcspn(str, "$\'\" \t\n\v\f\r<>|*/")}, T_STR});
}

static	t_token	get_one_token(t_state	*state, const char *str)
{
	if (*state == NORMAL && *str == '\n')
		return ((t_token){{str, 0}, T_END});
	if (*state == NORMAL && *str == '\'')
		return (*state = QUOTE, (t_token){{str, 1}, T_Q_START});
	if (*state == NORMAL && *str == '\"')
		return (*state = DQUOTE, (t_token){{str, 1}, T_DQ_START});
	if (*state == DQUOTE && *str == '\"')
		return (*state = NORMAL, (t_token){{str, 1}, T_DQ_END});
	if (*state == QUOTE && *str == '\'')
		return (*state = NORMAL, (t_token){{str, 1}, T_Q_END});
	if (*state == NORMAL && ft_strchr(" \t", *str))
		return ((t_token){{str, ft_strspn(str, "\t ")}, T_SPACE});
	if ((*state == NORMAL || *state == DQUOTE) && *str == '$')
		return ((t_token){{str, next_non_identifier(str) - str}, T_VAR});
	if (*state == N && (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "<<", 2)))
		return ((t_token){{str, 2}, *(str) + 1});
	if (*state == NORMAL && ft_strchr("<>|", *str))
		return ((t_token){{str, 1}, *str});
	if (*state == NORMAL && *str == '*')
		return ((t_token){{str, ft_strspn(str, "*")}, T_WILDCARD});
	return (get_one_token_cont(state, str));
}

bool	finish_lex(t_rlinfo_com rlinfo_com, const char *str, const char *og_str)
{
	ft_rl_set_offset(rlinfo_com.rlinfo, str);
	if (vector_append_elems(rlinfo_com.command, og_str, str - og_str))
		return (1);
	if (vector_null_term(rlinfo_com.command))
		return (1);
	return (0);
}

//output tokens may be nonsensical, like unterminated quote tokens
// or redirect tokens at the end of the list
//splits a string of text into tokens. will  initialize the vector
// returns 0 on success and populates the vector
// returns 1 on error and frees the vector
bool	split_to_tokens(const char *str, t_vector *vec_token,
			t_rlinfo_com rlinfo_com)
{
	t_token		curr;
	t_state		state;
	const char	*og_str;

	og_str = str;
	state = NORMAL;
	vector_init(vec_token, sizeof(t_token));
	while (*str)
	{
		curr = get_one_token(&state, str);
		if (vector_append(vec_token, &curr))
			return (vector_clear(vec_token), 1);
		str = curr.strview.start + curr.strview.size;
		if (curr.type == T_END)
			return (finish_lex(rlinfo_com, str, og_str), 0);
	}
	curr = (t_token){{str, 0}, T_END};
	if (vector_append(vec_token, &curr))
		return (vector_clear(vec_token), 1);
	return (finish_lex(rlinfo_com, str, og_str), 0);
}
