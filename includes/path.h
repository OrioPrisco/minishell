/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 20:01:38 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/08/06 20:09:35 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

typedef enum e_free_mode {
	FREE_ON_ERROR = 1 << 0,
	FREE_ON_SUCCESS = 1 << 1,
	FREE_ALWAYS = FREE_ON_ERROR | FREE_ON_SUCCESS,
}	t_free_mode;

char	*path_concat(const char *folder, const char *item);
char	*path_concat_free(char *folder, char *item,
			t_free_mode folder_mode, t_free_mode item_mode);

#endif
