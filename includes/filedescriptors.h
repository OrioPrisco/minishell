/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedescriptors.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:23:35 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/21 16:07:43 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEDESCRIPTORS_H
# define FILEDESCRIPTORS_H

# include "tokens.h"
# include "stringview.h"

//	fd_cloexec is a flag that indicates the fd should be closed when execve
//	returns succussfully

typedef struct s_fds
{
	int				fd;
	int				fd_cloexec;
	char			*fn;
}			t_fds;

//	fd_utils.c
int		open_trunc(t_fds *fds, const char *fn, int flags);
int		open_append(t_fds *fds, const char *fn, int flags);
int		open_redirects(t_vector *tokens, int start, int stop, t_vector *vec_fds);

//	fd_utils_2.c
void	print_open_redirects(t_fds *fds, int size);
int		close_open_redirects(t_vector *vec_fds);
int		dup_to_lget(t_vector *vec_fds, t_fds *current);

#endif
