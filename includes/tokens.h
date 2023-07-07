/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:48:18 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/07/07 17:43:56 by OrioPrisco       ###   ########.fr       */
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

typedef struct s_token {
	t_stringview	strview;
	t_token_type	type;
}	t_token;

int			is_identifier_char(int c);
const char	*token_type_to_str(t_token_type type);
char		*next_non_identifier(const char *str);
bool		split_to_tokens(const char *str, t_vector *vec_token);
bool		process_quotes(t_vector *vec_token);

#endif
