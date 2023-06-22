/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:38:29 by dpentlan          #+#    #+#             */
/*   Updated: 2023/06/22 18:03:21 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prompt_loop(char **env)
{
	char	*str_input;

	if (env)
	{
	}
	str_input = 0;
	str_input = (char *)malloc(100 * sizeof(char));
	if (!str_input)
		ms_error("malloc");
	str_input = readline("> ");
	ft_printf("%s\n", str_input);
	free(str_input);
	return (0);
}
