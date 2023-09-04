/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:08:04 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/04 16:22:06 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include "tokens.h"

typedef struct s_vector	t_vector;

typedef struct s_cominfo
{
	char		*command;
	char		**envp;
	t_vector	*com_list;
}				t_cominfo;

typedef struct s_com_segment
{
	t_vector	*tokens;
	int			start;
	int			stop;
	int			size;
}				t_com_segment;

typedef struct s_pipe_info
{
	int			pipefd[2];
	int			old_pipe;
}				t_pipe_info;

//	Defines
# define HISTORY_FILE_PATH "HOME"
# define HISTORY_FILE_NAME ".msh_history"

//	prompt_utils.c
int		prompt_loop(char **env);

//	error_utils.c
void	msh_error(const char *message);
void	msh_exit(char **envp, t_vector *com_list);

//	history.c
bool	save_history(char **env, t_vector *com_list);
bool	load_in_history(char **env);
void	history_loop_logic(t_cominfo *cominfo);

//	signal_utils.c
void	sigint_handler(int signum);
void	sigquit_handler(int signum);

//	ast_utils.c
int		tree_crawler(t_vector *tokens, t_cominfo *cominfo);
void	cleanup_redirects(t_vector *vec_fds);
int		check_and_open_redirects(t_vector *tokens, t_vector *vec_fds,
			int start, int stop);

//	pipe_loop.c
int		pipe_loop(t_vector *tokens, t_cominfo *cominfo, t_vector *pipes);
int		fork_loop(t_vector *tokens, t_cominfo *cominfo, t_vector *pids);

//	fork_utils.c
int		msh_wait(t_vector *pids);
int		print_execve_args(char **execve_com_args);
char	**construct_execve_args(t_com_segment com_seg, char **execve_com_args);
int		single_fork(t_vector *tokens, t_cominfo *cominfo, t_vector *pids);
int		pipe_setup(t_vector *tokens, t_cominfo *cominfo, t_vector *pids);
int		multi_fork(t_com_segment com_seg, t_cominfo *cominfo, t_vector *pids,
			t_pipe_info *pipeinfo);

//	heredoc_utils.c
int		print_here_doc_contents(int heredoc_fd);
int		check_and_open_heredoc(t_vector *tokens, int start, int stop,
			t_cominfo *cominfo);

//	access_utils.c
void	print_access_debug(char *execve_command);
char	*access_loop(const char *command, char **envp);
char	*find_executable(t_cominfo *cominfo, t_com_segment com_segment);
void	access_error_print(const char *exec_name);
int		check_for_builtins(const char *exec_name);
void	exec_command(t_cominfo *cominfo, t_com_segment com_segment,
			t_vector *vec_fds);
void	builtin_commands(char *execve_command, char **execve_com_args,
			char **envp);

#endif
