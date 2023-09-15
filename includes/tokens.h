/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:48:18 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/09/15 13:51:03 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "stringview.h"
# include <stdbool.h>

//	current environment and the previous process return value.

typedef struct s_vector		t_vector;
typedef struct s_env_ret	t_env_ret;
typedef struct s_ft_rl		t_ft_rl;

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

// -- parse_line internals

typedef struct s_token {
	t_stringview	strview;
	t_token_type	type;
}	t_token;

typedef struct s_rlinfo_com {
	t_ft_rl		*rlinfo;
	t_vector	*command;
}	t_rlinfo_com;

// tokenizer
bool		split_to_tokens(const char *str, t_vector *vec_token,
				t_rlinfo_com rlinfo_com);

// parse_line_internals
int			parse_redirect(t_vector *dest, const t_token *tok,
				const t_env_ret *env_ret, t_rlinfo_com rlinfocom);
int			parse_pipe(t_vector *dest, const t_token *tok);
bool		merge_tokens(char **dest, const t_token *src, size_t to_merge,
				const t_env_ret *env_ret);
int			parse_text(t_vector *dest, const t_token *tok,
				const t_env_ret *env_ret);
int			parse_wildcard(t_vector *dest, const t_token *tok,
				const t_env_ret *env_ret, int to_merge);
int			seek_tokens_to_merge(const t_token *src);
int			open_heredoc(const char *limiter, const t_env_ret *env_ret,
				t_rlinfo_com rlinfo_com);

// --
int			parse_line(char **line, t_vector *dest,
				t_env_ret *env_ret, t_ft_rl *rlinfo);

#endif
