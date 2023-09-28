/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:24:26 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/28 11:54:55 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

bool	check_for_builtins_pre_fork(t_com_segment com_segment);
int		builtins_pre_fork(t_com_segment com_segment, t_cominfo *cominfo);
int		check_for_builtins(const char *exec_name);
int		builtin_commands(char *execve_command, char **execve_com_args,
			t_cominfo *cominfo);
void	builtins_cleanup(t_cominfo *cominfo, t_com_segment *com_seg, int ret);

int		echo_msh(char *execve_command, char **execve_com_args, char **envp);
int		cd_arg_parse_msh(char **execve_com_args, t_vector *env_vec);
int		pwd_msh(char *execve_command, char **execve_com_args,
			t_vector *env_vec);
int		export_msh(char *execve_command, char **execve_com_args,
			t_vector *env_vec);
int		unset_msh(char *execve_command, char **execve_com_args,
			t_vector *env_vec);
int		env_msh(char *execve_command, char **execve_com_args,
			t_vector *env_vec);
void	exit_msh(t_cominfo *cominfo, char **execve_com_args, int save_hist);

#endif
