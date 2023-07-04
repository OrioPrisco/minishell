/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:08:04 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/04 10:23:10 by dpentlan         ###   ########.fr       */
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

//	command struct
typedef struct s_command
{
	char	*s_com;
	char	**args;
}				t_command;

//	ms_prompt_utils.c
int	prompt_loop(char **env);

//	ms_error_utils.c
int	ms_error(char *message);

//	ms_history.c
int	add_com_to_history(char *str_input);

#endif
