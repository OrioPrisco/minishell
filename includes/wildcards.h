/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:58:33 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/08/17 15:02:55 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARDS_H
# define WILDCARDS_H

# include <stdbool.h>
# include <stddef.h>

# ifndef WILDCARD_IN_CWD
#  define WILDCARD_IN_CWD 1
# endif

typedef struct s_owned_token	t_owned_token;
typedef struct s_token			t_token;
typedef struct s_vector			t_vector;

bool	expand_wildcard(const t_token *expr, const char *cwd, t_vector *dest);
bool	compile_wildcard_expr(const t_owned_token *src, t_vector *dest);
bool	substitute_all_wildcards(t_vector *vector);
#endif
