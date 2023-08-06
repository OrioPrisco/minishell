/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:31:12 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/08/06 20:29:38 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "path.h"

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

char	*path_concat_free(char *folder, char *item,
	t_free_mode folder_mode, t_free_mode item_mode)
{
	char	*temp;

	temp = path_concat(folder, item);
	if (temp && folder_mode & FREE_ON_SUCCESS)
		free(folder);
	if (!temp && folder_mode & FREE_ON_ERROR)
		free(folder);
	if (temp && item_mode & FREE_ON_SUCCESS)
		free(item);
	if (!temp && folder_mode & FREE_ON_ERROR)
		free(item);
	return (temp);
}
