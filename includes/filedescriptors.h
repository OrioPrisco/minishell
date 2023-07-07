/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedescriptors.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:23:35 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/07 14:46:18 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEDESCRIPTORS_H
# define FILEDESCRIPTORS_H

# include "tokens.h"
# include "stringview.h"

typedef struct s_fds
{
	int				fd;
	char			*fn;
}			t_fds;

//	fd_utils.c
void	free_redirects_fn(t_fds *fds, int size);
void	print_open_redirects(t_fds *fds, int size);
t_fds	*open_redirects(t_token *tokens, int size, t_vector *fds);

#endif
