/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:48:18 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/07/12 11:42:26 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "stringview.h"
# include <stdbool.h>

typedef struct s_vector	t_vector;

// explicit values are used in code and shouldn't be changed
typedef enum e_token_type {
	T_SPACE,
	T_Q_STR = '\'',
	T_DQ_STR = '\"',
	T_STR,
	T_END,
	T_REDIRECT_STDOUT = '>',
	T_REDIRECT_STDIN = '<',
	T_HEREDOC = '<' + 1,
	T_REDIRECT_STDOUT_APPEND = '>' + 1,
	T_PIPE = '|',
	T_VAR,
}	t_token_type;

// internal to parse line

// like token but the string is owned by the token
typedef struct s_owned_token {
	char			*str;
	t_token_type	type;
}	t_owned_token;

// -- utils
int			is_identifier_char(int c);
const char	*token_type_to_str(t_token_type type);
char		*next_non_identifier(const char *str);

// -- parse_line internals

typedef struct s_token {
	t_stringview	strview;
	t_token_type	type;
}	t_token;

bool		split_to_tokens(const char *str, t_vector *vec_token);
bool		process_quotes(t_vector *vec_token);
bool		split_dquoted_tokens(t_vector *vec_token);
void		expand_vars(t_vector *vec_token, char **envp);
bool		merge_tokens(t_vector *dest_owned_tok, const t_vector *src_tokens);
// --
bool		parse_line(const char *line, t_vector *dest, char **envp);

#endif
