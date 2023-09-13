/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:08:04 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/13 13:26:37 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include "tokens.h"

typedef struct s_vector		t_vector;
typedef struct s_env_ret	t_env_ret;

typedef struct s_cominfo
{
	char		*command;
	t_env_ret	*env_ret;
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
int		prompt_loop(char **envp);

//	error_utils.c
void	msh_error(const char *message);
void	msh_exit(t_cominfo *cominfo);

//	history.c
bool	save_history(const t_env_ret *env_ret, t_vector *com_list);
bool	load_in_history(const t_env_ret *env_ret);
void	history_loop_logic(t_cominfo *cominfo);

//	signal_utils.c
void	sigint_handler_parent(int signum);
void	sigint_handler_child(int signum);
void	sigint_handler_heredoc(int signum);
int		signal_assign(int signal, void (*f)(int));

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
int		single_fork(t_vector *tokens, t_cominfo *cominfo, t_vector *pids,
			t_pipe_info *pipeinfo);
int		pipe_setup(t_vector *tokens, t_cominfo *cominfo, t_vector *pids,
			t_pipe_info *pipeinfo);
int		multi_fork(t_com_segment com_seg, t_cominfo *cominfo, t_vector *pids,
			t_pipe_info *pipeinfo);

//	heredoc_utils.c
int		print_here_doc_contents(int heredoc_fd);
int		check_and_open_heredoc(t_vector *tokens, int start, int stop,
			t_cominfo *cominfo);

//	access_utils.c
void	print_access_debug(char *execve_command);
char	*access_loop(const char *command, const t_env_ret *env_ret);
char	*search_env(char *exec_name, t_cominfo *cominfo,
			t_com_segment *com_segment);
void	access_error_print(const char *exec_name);
int		check_for_builtins(const char *exec_name);
int		check_for_builtins_pre_fork(t_com_segment com_segment, t_cominfo *cominfo);
void	exec_command(t_cominfo *cominfo, t_com_segment com_segment,
			t_vector *vec_fds);
void	builtin_commands(char *execve_command, char **execve_com_args,
			char **envp);
char	*get_exec_name(t_owned_token *token);
void	builtins_pre_fork(char *exec_name, t_com_segment com_segment,
			t_cominfo *cominfo);

#endif
