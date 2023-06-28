/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:08:04 by dpentlan          #+#    #+#             */
/*   Updated: 2023/06/22 18:01:12 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include "../libft/includes/libft.h"
# include "ft_printf.h"

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

#endif
