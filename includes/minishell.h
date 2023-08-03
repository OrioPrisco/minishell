/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:08:04 by dpentlan          #+#    #+#             */
/*   Updated: 2023/08/03 13:06:32 by dpentlan         ###   ########.fr       */
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
int		single_command(t_vector *tokens, int start, int stop,
			t_cominfo *cominfo);

//	pipe_loop.c
int		pipe_loop(t_vector *tokens, t_cominfo *cominfo, t_vector *pipes);
int		fork_loop(t_vector *tokens, t_cominfo *cominfo, t_vector *pids);

//	fork_utils.c
int		msh_wait(t_vector *pids);

//	heredoc_utils.c
int		print_here_doc_contents(int heredoc_fd);
int		check_and_open_heredoc(t_vector *tokens, int start, int stop,
			t_cominfo *cominfo);

//	access_utils.c
bool	add_slash_and_command(char **path, int i, char *command);
bool	add_command_to_single_path_item(char **path, int i, char *command);
void	print_access_debug(char *execve_command);
char	*access_loop(t_owned_token *token, char **envp);

#endif
