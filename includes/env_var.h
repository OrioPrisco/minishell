/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 22:10:31 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/09/08 14:27:24 by OrioPrisco       ###   ########.fr       */
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

#endif
