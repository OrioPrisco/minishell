/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_int.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:13:21 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/10/05 16:48:51 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INT_H
# define PARSER_INT_H

# include "stringview.h"
# include "tokens.h"

typedef struct s_ft_rl		t_ft_rl;
typedef struct s_env_ret	t_env_ret;

typedef struct s_token {
	t_stringview	strview;
	t_token_type	type;
}	t_token;

typedef struct s_rlinfo_com {
	t_ft_rl			*rlinfo;
	t_vector		*command;
	const t_env_ret	*env_ret;
}	t_rlinfo_com;

// tokenizer

typedef enum e_state
{
	NORMAL = 0,
	QUOTE = 1 << 0,
	DQUOTE = 1 << 1,
	N_MASK = 0x3,
	AFTER_HD = 1 << 2,
	AFTER_HD_TXT = 1 << 3,
	HD_MASK = AFTER_HD | AFTER_HD_TXT,
	N = NORMAL,
	Q = QUOTE,
	DQ = DQUOTE,
	N_M = N_MASK,
}	t_state;

bool		split_var_to_tokens(const char *var, t_vector *dest,
				t_state state);
bool		split_to_tokens(const char *str, t_vector *vec_token,
				t_rlinfo_com rlinfo_com);

// parse_line_internals
int			parse_redirect(t_vector *dest, const t_token *tok,
				t_rlinfo_com rlinfocom);
int			parse_pipe(t_vector *dest, const t_token *tok);
bool		merge_tokens(char **dest, const t_token *src, size_t to_merge,
				const t_env_ret *env_ret);
int			parse_text(t_vector *dest, const t_token *tok,
				const t_env_ret *env_ret, bool force_output);
int			parse_wildcard(t_vector *dest, const t_token *tok,
				int to_merge);
int			seek_tokens_to_merge(const t_token *src);
int			open_heredoc(const char *limiter,
				t_rlinfo_com rlinfo_com);
void		syntax_error(t_token_type type);

#endif
