/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:58:59 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/05 17:44:21 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHILD_H
# define CHILD_H

# include "minishell.h"

void	single_command(t_com_segment com_seg, t_cominfo *cominfo,
			t_pipe_info *pipeinfo);
void	msh_exit_child(t_vector *com_list);
void	exec_error(t_vector *vec_fds, t_cominfo *cominfo);

#endif
