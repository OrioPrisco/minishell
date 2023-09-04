/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:48:18 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/09/05 20:35:19 by OrioPrisco       ###   ########.fr       */
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
	T_STR,
	T_END,
	T_Q_START,
	T_Q_END,
	T_DQ_START,
	T_DQ_END,
	T_VAR,
	T_WILDCARD,
	T_DIR_SEP,
	T_REDIRECT_STDOUT = '>',
	T_REDIRECT_STDIN = '<',
	T_HEREDOC = '<' + 1,
	T_REDIRECT_STDOUT_APPEND = '>' + 1,
	T_PIPE = '|',
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
void		print_tokens(t_vector *owned_tokens);
void		print_relavent_tokens(t_vector *owned_tokens, int start, int stop);
void		free_owned_token(void *owned_token);
bool		is_text_type(t_token_type type);
bool		is_redirect_type(t_token_type type);
bool		is_wildcard_expr_type(t_token_type type);

//internal to token_type_to_str
typedef struct s_tok_map_entry
{
	t_token_type	type;
	const char		*str;
}	t_tok_map_entry;

// -- parse_line internals

typedef struct s_token {
	t_stringview	strview;
	t_token_type	type;
}	t_token;

bool		split_to_tokens(const char *str, t_vector *vec_token);
bool		process_quote(t_token *token);
bool		process_redirect(t_token *token);
bool		validate_pipe(const t_token *token);
bool		split_dquoted_tokens(t_vector *vec_token);
void		expand_vars(t_vector *vec_token, char **envp);
bool		merge_tokens(t_vector *dest_owned_tok, const t_vector *src_tokens);
bool		process_one_token(t_token *token);
// --
bool		parse_line(const char *line, t_vector *dest, char **envp);

#endif
