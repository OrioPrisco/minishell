/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:34:07 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/08/11 14:43:58 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include "ft_printf.h"

void	free_str(void *data)
{
	char	**str;

	str = data;
	free(*str);
}

/*	*** table_free (table free) ***
 *
 *	Frees a char ** table created by ft_split.
 *	Takes a table to free 'table'.
 *	Returns nothing.
 */

void	table_free(char **table)
{
	int	i;

	i = 0;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
	return ;
}

/*	*** table_print (print table) ***
 *
 *	Prints the contents of a table (char **).
 *	Takes a char table (char **).
 *	Returns nothing.
 */

void	table_print(char **table)
{
	int	i;

	i = 0;
	while (table[i])
	{
		ft_printf("%02d. %s\n", i, table[i]);
		i++;
	}
	return ;
}
