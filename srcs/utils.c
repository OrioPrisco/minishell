/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:34:07 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/09/26 15:08:54 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

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

int	compare_str(void *a, void *b)
{
	char	**astr;
	char	**bstr;

	astr = a;
	bstr = b;
	return (-ft_fake_strcoll(*astr, *bstr));
}

void	close_fd(void *to_close)
{
	int	*current;

	current = to_close;
	close(*current);
}
