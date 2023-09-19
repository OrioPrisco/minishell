/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:48:18 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/09/19 13:55:08 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "stringview.h"
# include <stdbool.h>

//	current environment and the previous process return value.

typedef struct s_vector		t_vector;

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

typedef struct s_owned_token {
	char			*str;
	t_token_type	type;
	int				hd;
}	t_owned_token;

// -- utils
int			is_identifier_char(int c);
const char	*token_type_to_str(t_token_type type);
char		*next_non_identifier(const char *str);
void		print_tokens(t_vector *owned_tokens);
void		print_relavent_tokens(t_vector *owned_tokens, int start, int stop);
void		free_owned_token(void *owned_token);
bool		is_textexpr_type(t_token_type type);
bool		is_text_type(t_token_type type);
bool		is_redirect_type(t_token_type type);

//internal to token_type_to_str
typedef struct s_tok_map_entry
{
	t_token_type	type;
	const char		*str;
}	t_tok_map_entry;

#endif
