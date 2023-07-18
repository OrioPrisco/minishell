/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:08:04 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/18 15:40:49 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>

typedef struct s_vector	t_vector;

//	Defines
# define HISTORY_FILE_PATH "HOME"
# define HISTORY_FILE_NAME ".msh_history"

//	prompt_utils.c
int		prompt_loop(char **env);

//	error_utils.c
void	msh_error(const char *message);
void	msh_exit(char **env, t_vector *com_list);

//	history.c
bool	save_history(char **env, t_vector *com_list);
bool	load_in_history(char **env);
void	history_loop_logic(char *str_input, t_vector *com_list);

//	signal_utils.c
void	sigint_handler(int signum);
void	sigquit_handler(int signum);

//	ast_utils.c
int		tree_crawler(t_vector *tokens);

#endif
