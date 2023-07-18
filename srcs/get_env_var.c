/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 21:39:05 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/07/18 17:15:29 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env_var.h"

//does not check that name is a valid identifier
//has special cases for $ and $?
// TODO : handle $? properly
//name size hs te be correct
const char	*get_env_var(char **envp, const char *name, size_t name_size)
{
	if (name_size == 1 && *name == '$')
		return ("$");
	if (name_size == 2 && !ft_memcmp(name, "$?", 2))
		return ("TODO_RETURN_CODE");
	if (*name == '$')
	{
		name++;
		name_size--;
	}
	while (*envp)
	{
		if (!ft_memcmp(name, *envp, name_size) && (*envp)[name_size] == '=')
			return (*envp + name_size + 1);
		envp++;
	}
	return (NULL);
}
