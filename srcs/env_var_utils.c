/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:14:45 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/09/22 12:15:19 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_var.h"
#include "libft.h"

//returns whether a character is alphanumeric or _
//careful, identifier cannot start with a digit.
//use next_non_indetifier to check entire strings
int	is_identifier_char(int i)
{
	char	c;

	c = i;
	return (c == '_' || ft_isalnum(i));
}

//returns a pointer to first character that is not
// part of a valid identifier
//the string may start with $, which will be skipped
//the return pointer may point to the terminating nul byte if
//the entire string is a valid identifier
//handles the special case $?
char	*next_non_identifier(const char *str)
{
	if (!ft_strncmp(str, "$?", 2))
		return ((char *)str + 2);
	if (*str == '$')
		str++;
	if (!(ft_isalpha(*str) || *str == '_'))
		return ((char *)str);
	str++;
	while (*str && is_identifier_char(*str))
		str++;
	return ((char *)str);
}
