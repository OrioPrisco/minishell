/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:08:04 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/05 11:06:04 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "ft_printf.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include <signal.h>

//	command struct
typedef struct s_command
{
	char	*s_com;
	char	**args;
}				t_command;

//	prompt_utils.c
int		prompt_loop(char **env);

//	error_utils.c
void	msh_error(char *message);
void	msh_exit(void);

//	history.c
bool	load_in_history(void);
bool	add_com_to_history(char *str_input);

//	signal_utils.c
void	sigint_handler(int signum);
void	sigquit_handler(int signum);

#endif
