/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:08:04 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/22 14:36:17 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include "tokens.h"
# include "vector.h"

typedef struct s_env_ret	t_env_ret;
typedef struct s_ft_rl		t_ft_rl;

typedef struct s_cominfo
{
	t_env_ret	*env_ret;
	t_vector	com_list;
	t_ft_rl		*rlinfo;
	t_vector	*tokens;
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
void	prompt_loop(char **envp);

//	error_utils.c
void	msh_error(const char *message);
void	msh_exit(t_cominfo *cominfo, int ret_code, int save_his);

//	history.c
int		save_history(const t_env_ret *env_ret, t_vector *com_list);
int		load_in_history(const t_env_ret *env_ret);
int		history_loop_logic(t_vector *com_list, char *str);

//	ast_utils.c
int		tree_crawler(t_vector *tokens, t_cominfo *cominfo);
int		check_and_open_redirects(t_vector *tokens, t_vector *vec_fds,
			int start, int stop);

//	pipe_loop.c
int		pipe_loop(t_vector *tokens, t_cominfo *cominfo, t_vector *pipes);
int		fork_loop(t_vector *tokens, t_cominfo *cominfo, t_vector *pids);

//	fork_utils.c
int		msh_wait(t_vector *pids, int *ret_status);
int		print_execve_args(char **execve_com_args);
char	**construct_execve_args(t_com_segment com_seg);
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
void	exec_command(t_cominfo *cominfo, t_com_segment com_segment);
char	*get_exec_name(t_owned_token *token);

#endif
