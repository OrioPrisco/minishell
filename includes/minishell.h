/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:08:04 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/29 11:22:39 by dpentlan         ###   ########.fr       */
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
int		tree_crawler(t_vector *tokens, char **envp);
int		single_command(t_vector *tokens, int start, int stop, char **envp);

//	pipe_loop.c
int		pipe_loop(t_vector *tokens, int size, char **envp);

//	heredoc_utils.c
int		check_and_open_heredoc(t_vector *tokens, int start, int stop);

//	access_utils.c
char	*access_loop(t_vector *tokens, int start, char **envp);

#endif
