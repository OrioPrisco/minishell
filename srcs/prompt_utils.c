/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:38:29 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/04 10:43:00 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_prompt_loop(void)
{
	load_in_history();
	return (0);
}

int	prompt_loop(char **env)
{
	char	*str_input;

	init_prompt_loop();
	if (env)
	{
	}
	str_input = readline("> ");
	if (!str_input)
		ms_error("malloc");
	add_com_to_history(str_input);
	add_history(str_input);
	ft_printf("%s\n", str_input);
	free(str_input);
	return (0);
}
