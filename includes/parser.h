/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:07:25 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/09/18 13:10:24 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

typedef struct s_owned_token	t_owned_token;
typedef struct s_vector			t_vector;
typedef struct s_env_ret		t_env_ret;
typedef struct s_ft_rl			t_ft_rl;

int			parse_line(char **line, t_vector *dest,
				t_env_ret *env_ret, t_ft_rl *rlinfo);

#endif
