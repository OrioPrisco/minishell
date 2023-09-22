/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:44:27 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/22 16:06:29 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_var.h"
#include "ft_printf.h"
#include "libft.h"
#include <stdlib.h>
#include "error.h"

size_t	check_env_vec_dup(t_vector *env_vec, const char *s1, size_t n)
{
	size_t	i;

	i = 0;
	while (i < env_vec->size)
	{
		if (!ft_strncmp(((char **)env_vec->data)[i], s1, n + 1))
			return (i);
		i++;
	}
	return (i);
}

int	del_from_env_vec(t_vector *env_vec, size_t index)
{
	char	*temp;

	if (index >= env_vec->size)
		return (0);
	vector_pop(env_vec, index, &temp);
	vector_null_term(env_vec);
	free(temp);
	return (0);
}

int	add_str_to_env_vec(t_vector *env_vec, char *str)
{
	char	*buf;

	buf = next_non_identifier(str);
	del_from_env_vec(env_vec, check_env_vec_dup(env_vec, str, buf - str));
	if (!str)
		return (0);
	buf = ft_strdup(str);
	if (!buf)
		return (msh_error("malloc"), -1);
	if (vector_append(env_vec, &buf))
		return (msh_error("malloc"), -1);
	if (vector_null_term(env_vec))
		return (msh_error("malloc"), -1);
	return (0);
}

int	print_env_vec(t_vector *env_vec, char *str)
{
	size_t	i;

	i = 0;
	while (i < env_vec->size)
	{
		ft_printf("%s%s\n", str, ((char **)env_vec->data)[i]);
		i++;
	}
	return (0);
}

int	add_key_value_to_env_vec(char *env_to_change, char *cwd, t_vector *env_vec)
{
	char	*env_comp;

	env_comp = ft_strjoin(env_to_change, cwd);
	if (!env_comp)
		return (msh_error("malloc"), free(cwd), -1);
	if (add_str_to_env_vec(env_vec, env_comp))
		return (free(env_comp), -1);
	return (free(env_comp), 0);
}
