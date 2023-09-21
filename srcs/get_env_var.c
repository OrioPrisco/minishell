/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 21:39:05 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/09/21 16:23:25 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env_var.h"
#include "vector.h"

static void	putnbr_buff(char **buff, long int number)
{
	if (number < 0)
	{
		buff[0][0] = '-';
		(*buff)++;
		putnbr_buff(buff, -number);
	}
	else
	{
		if (number >= 10)
			putnbr_buff(buff, number / 10);
		buff[0][0] = "0123456789"[number % 10];
		buff[0][1] = 0;
		(*buff)++;
	}
}

// will work as long as the string is duplicated
// before this gets called with another value
const char	*get_number(int number)
{
	static int	last;
	static char	buffer[12] = "0";
	char		*buff_cpy;

	buff_cpy = buffer;
	if (number == last)
		return (buffer);
	putnbr_buff(&buff_cpy, number);
	last = number;
	return (buffer);
}

const char	*get_env_var_no_special(char **envp, const char *name,
				size_t name_size)
{
	size_t	i;

	if (*name == '$')
	{
		name++;
		name_size--;
	}
	i = 0;
	while (envp[i])
	{
		if (!ft_memcmp(name, envp[i], name_size) && envp[i][name_size] == '=')
			return (envp[i] + name_size + 1);
		i++;
	}
	return (NULL);
}

//does not check that name is a valid identifier
//has special cases for $ and $?
//name size hs te be correct
const char	*get_env_var(const t_env_ret *env_ret, const char *name,
				size_t name_size)
{
	if (name_size == 1 && *name == '$')
		return ("$");
	if (name_size == 2 && !ft_memcmp(name, "$?", 2))
		return (get_number(env_ret->prev_ret));
	return (get_env_var_no_special(env_ret->env_vec.data, name, name_size));
}

// same as get_env_var but returns an empty string instead of null
const char	*get_env_varnul(const t_env_ret *env_ret, const char *name,
				size_t name_size)
{
	const char	*ret;

	ret = get_env_var(env_ret, name, name_size);
	if (!ret)
		return ("");
	return (ret);
}
