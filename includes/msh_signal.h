/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:51:37 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/09/19 16:01:15 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_SIGNAL_H
# define MSH_SIGNAL_H

typedef enum e_trigger {
	NONE,
	HD_SIGINT,
	PARENT_SIGINT,
}	t_trigger;

//	signal_utils.c
void	sigint_handler_parent(int signum);
void	sigint_handler_child(int signum);
void	sigint_handler_heredoc(int signum);
int		signal_assign(int signal, void (*f)(int));

extern volatile int	g_sig_triggered;

#endif
