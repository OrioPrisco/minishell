/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:52:58 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/10/05 16:58:46 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tokens.h"
#include "vector.h"
#include "ft_readline.h"
#include "parser_int.h"
#include "env_var.h"

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
	if (*state & DQUOTE)
		return ((t_token){{str, ft_strcspn(str, "$\"/")}, T_STR});
	if (*state & QUOTE)
		return ((t_token){{str, ft_strcspn(str, "\'/")}, T_STR});
	return ((t_token){{str, ft_strcspn(str, "$\'\" \t\n\v\f\r<>|*/")}, T_STR});
}

static	t_token	get_one_token_1(t_state	*state, const char *str)
{
	if (!(*state & N_MASK) && *str == '\n')
		return ((t_token){{str, 0}, T_END});
	if (!(*state & N_MASK) && *str == '\'')
		return (*state &= ~N_M, *state |= Q, (t_token){{str, 1}, T_Q_START});
	if (!(*state & N_MASK) && *str == '\"')
		return (*state &= ~N_M, *state |= DQ, (t_token){{str, 1}, T_DQ_START});
	if (*state & DQUOTE && *str == '\"')
		return (*state &= ~N_MASK, (t_token){{str, 1}, T_DQ_END});
	if (*state & QUOTE && *str == '\'')
		return (*state &= ~N_MASK, (t_token){{str, 1}, T_Q_END});
	if (!(*state & N_MASK) && ft_strchr(" \t", *str))
		return ((t_token){{str, ft_strspn(str, "\t ")}, T_SPACE});
	if ((!(*state & N_MASK) || *state & DQUOTE) && *str == '$')
		return ((t_token){{str, next_non_identifier(str) - str}, T_VAR});
	if (!(*state & N_MASK)
		&& (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "<<", 2)))
		return ((t_token){{str, 2}, *(str) + 1});
	if (!(*state & N_MASK) && ft_strchr("<>|", *str))
		return ((t_token){{str, 1}, *str});
	if (!(*state & N_MASK) && *str == '*')
		return ((t_token){{str, ft_strspn(str, "*")}, T_WILDCARD});
	return (get_one_token_cont(state, str));
}

// handles HD state logic
static	t_token	get_one_token(t_state *state, const char *str)
{
	t_token	token;

	token = get_one_token_1(state, str);
	if (token.type == T_HEREDOC)
		*state |= AFTER_HD;
	else if (*state & AFTER_HD && is_textexpr_type(token.type))
		*state ^= AFTER_HD | AFTER_HD_TXT;
	else if (*state & AFTER_HD_TXT && !is_textexpr_type(token.type))
		*state &= ~HD_MASK;
	return (token);
}

bool	finish_lex(t_rlinfo_com rlinfo_com, const char *str, const char *og_str)
{
	if (vector_append_elems(rlinfo_com.command, og_str, str - og_str))
		return (1);
	if (*str == '\n')
		str++;
	ft_rl_add_offset(rlinfo_com.rlinfo, str - og_str);
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
	while (*str)
	{
		curr = get_one_token(&state, str);
		if ((curr.type != T_VAR || state & HD_MASK)
			&& vector_append(vec_token, &curr))
			return (vector_clear(vec_token), 1);
		if ((curr.type == T_VAR && !(state & HD_MASK))
			&& split_var_to_tokens(get_env_var(
					rlinfo_com.env_ret, curr.strview.start, curr.strview.size
				), vec_token, state))
			return (vector_clear(vec_token), 1);
		str = curr.strview.start + curr.strview.size;
		if (curr.type == T_END)
			return (finish_lex(rlinfo_com, str, og_str));
	}
	curr = (t_token){{str, 0}, T_END};
	if (vector_append(vec_token, &curr))
		return (vector_clear(vec_token), 1);
	return (finish_lex(rlinfo_com, str, og_str));
}
