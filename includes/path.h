/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 20:01:38 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/08/09 16:21:32 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

typedef struct s_vector	t_vector;

char	*path_concat(const char *folder, const char *item);
int		get_dir_files(t_vector *dest, const char *folder);

#endif
