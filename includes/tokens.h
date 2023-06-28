/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:48:18 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/06/28 17:08:56 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

// things like > >> < << | should be tokens
typedef enum e_token_type {
	T_SPACE = ' ',
	T_Q_STR = '\'',
	T_DQ_STR = '\"',
	T_STR = 's',
	T_END = 'e',
}	t_token_type;

typedef struct s_token {
	char			*opt_str;
	t_token_type	type;
}	t_token;

#endif
