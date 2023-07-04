/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:08:04 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/04 19:42:56 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/includes/libft.h"
# include "ft_printf.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>

//	command struct
typedef struct s_command
{
	char	*s_com;
	char	**args;
}				t_command;

//	prompt_utils.c
int		prompt_loop(char **env);

//	error_utils.c
int		ms_error(char *message);

//	history.c
bool	load_in_history(void);
bool	add_com_to_history(char *str_input);

#endif
