/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:31:12 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/08/10 20:51:11 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "path.h"
#include <dirent.h>
#include <errno.h>
#include "utils.h"
#include "vector.h"
#include <sys/stat.h>

//concatenates a folder name with another string
// the output will have a / between folder and item
// even if folder does not contain a /
//return NULL on error
//if folder is empty, returns a duplicate of item,
// as if folder was the cwd
//does not check if item starts with a / or not
char	*path_concat(const char *folder, const char *item)
{
	size_t	folder_len;
	char	*temp;
	char	*temp2;

	folder_len = ft_strlen(folder);
	if (!folder_len)
		return (ft_strdup(item));
	if (folder[folder_len - 1] == '/')
		return (ft_strjoin(folder, item));
	temp = ft_strjoin(folder, "/");
	if (!temp)
		return (NULL);
	temp2 = ft_strjoin(temp, item);
	free(temp);
	return (temp2);
}

// gets all files in a directory
// will return an empty vector if not given a directory
// returns 0 on success and the vector will be initialised and populated
// returns 1 on malloc error and the vector will be cleared
// returns -1 in case of opendir/readdir/stat err and the vector will be cleared
int	get_dir_files(t_vector *dest, const char *folder)
{
	DIR				*directory;
	struct dirent	*dir_entry;
	int				is_dir;
	char			*str;

	vector_init(dest, sizeof(char *));
	is_dir = is_directory(folder);
	if (is_dir <= 0)
		return (is_dir);
	errno = 0;
	directory = opendir(folder);
	if (!directory)
		return (-1);
	dir_entry = readdir(directory);
	while (dir_entry)
	{
		str = ft_strdup(dir_entry->d_name);
		if (!str || vector_append(dest, &str))
			return (closedir(directory), vector_free(dest, free_str), 1);
		dir_entry = readdir(directory);
	}
	closedir(directory);
	if (errno)
		return (vector_clear(dest), -1);
	return (0);
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
