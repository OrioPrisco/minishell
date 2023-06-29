/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:48:18 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/06/29 16:05:14 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "stringview.h"

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
}	t_token_type;

typedef struct s_token {
	t_stringview	strview;
	t_token_type	type;
}	t_token;

#endif
