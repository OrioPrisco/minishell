/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:24:26 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/21 14:13:57 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

bool	check_for_builtins_pre_fork(t_com_segment com_segment);
int		builtins_pre_fork(t_com_segment com_segment, t_cominfo *cominfo);
int		check_for_builtins(const char *exec_name);
int		builtin_commands(char *execve_command, char **execve_com_args,
			t_vector *env_vec);
void	builtins_cleanup(t_cominfo *cominfo, t_com_segment *com_seg, int ret);

void	exit_msh(t_cominfo *cominfo, t_com_segment *com_segment);
int		echo_msh(char *execve_command, char **execve_com_args, char **envp);
int		cd_msh(char *execve_command, char **execve_com_args, char **envp);
int		pwd_msh(char *execve_command, char **execve_com_args, char **envp);
int		export_msh(char *execve_command, char **execve_com_args, t_vector *env_vec);
int		unset_msh(char *execve_command, char **execve_com_args, t_vector *env_vec);
int		env_msh(char *execve_command, char **execve_com_args, t_vector *env_vec);

size_t	check_env_vec_dup(t_vector *env_vec, const char *s1, size_t n);
int		add_to_env_vec(t_vector *env_vec, char *str);
int		del_from_env_vec(t_vector *env_vec, size_t index);
int		print_env_vec(t_vector *env_vec, char *str);

#endif
