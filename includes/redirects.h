/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedescriptors.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:23:35 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/26 15:42:17 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTS_H
# define REDIRECTS_H

# include <stdbool.h>

typedef struct s_vector		t_vector;
typedef struct s_pipe_info	t_pipe_info;

//	fd_utils.c
int		open_redirects(t_vector *tokens, int start, int stop,
			t_vector *vec_fds);
int		cleanup_pipes(t_pipe_info *pipeinfo);

#endif
