/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 20:01:38 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/08/17 14:49:45 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

# include <stdbool.h>

typedef struct s_vector	t_vector;

char	*path_concat(const char *folder, const char *item);
int		get_dir_files(t_vector *dest, const char *folder);
int		is_directory(const char *filename);
bool	is_in_cwd(const char *path);

#endif
