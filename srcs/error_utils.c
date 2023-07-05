/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:58:47 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/05 10:41:14 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_error(char *message)
{
	if (message)
		perror(message);
	else
		ft_putstr_fd("Error:", 2);
	exit(EXIT_FAILURE);
}

void	msh_exit(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(EXIT_SUCCESS);
}
