/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:34:07 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/08/30 17:37:25 by OrioPrisc        ###   ########.fr       */
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

// TODO: Need the comparison to have a < A < b < B
// Not adequate to compare things like ab/a vs a/ab
// however the subject only requires wildcards in cwd, this will work
int	compare_str(void *a, void *b)
{
	char	**astr;
	char	**bstr;

	astr = a;
	bstr = b;
	return (-ft_fake_strcoll(*astr, *bstr));
}
