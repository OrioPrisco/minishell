/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:34:07 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/08/08 16:10:40 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include <sys/stat.h>

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

//returns
// -1 on error, and errno gets set
// 0 if filename is not a directory
// 1 if filename is a directory
int	is_directory(const char *filename)
{
	struct stat	file_stat;

	if (stat(filename, &file_stat))
		return (-1);
	return (S_ISDIR(file_stat.st_mode));
}
