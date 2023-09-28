/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 22:10:31 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/09/28 11:54:52 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_VAR_H
# define ENV_VAR_H

# include <stddef.h>
# include "vector.h"

typedef struct s_env_ret
{
	t_vector	env_vec;
	int			prev_ret;
}				t_env_ret;

const char	*get_env_var(const t_env_ret *env_ret, const char *name,
				size_t name_size);
const char	*get_env_varnul(const t_env_ret *env_ret, const char *name,
				size_t name_size);
const char	*get_env_var_no_special(char **envp, const char *name,
				size_t name_size);
char		*next_non_identifier(const char *str);
int			is_identifier_char(int i);

size_t		check_env_vec_dup(t_vector *env_vec, const char *s1, size_t n);
int			add_str_to_env_vec(t_vector *env_vec, char *str);
int			del_from_env_vec(t_vector *env_vec, size_t index);
int			print_env_vec(t_vector *env_vec, char *str);
int			add_key_value_to_env_vec(char *env_to_change, char *cwd,
				t_vector *env_vec);
#endif
