/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_int.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:13:21 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/09/18 13:19:35 by OrioPrisc        ###   ########.fr       */
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

#endif
