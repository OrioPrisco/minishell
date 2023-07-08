/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedescriptors.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:23:35 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/08 09:02:34 by dpentlan         ###   ########.fr       */
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
	char			*fn;
	bool			fd_cloexec;
}			t_fds;

//	fd_utils.c
int		open_redirects(t_token *tokens, int size, t_vector *vec_fds);

//	fd_utils_2.c
void	free_redirects_fn(t_fds *fds, int size);
void	free_redirects_all(t_fds *fds, int size);
void	print_open_redirects(t_fds *fds, int size);
int		close_open_redirects(t_fds *fds, int size);
void	dup_to_lgett(t_vector *vec_fds, t_fds *current);

#endif
