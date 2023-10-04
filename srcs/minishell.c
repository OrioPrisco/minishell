/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:06:11 by dpentlan          #+#    #+#             */
/*   Updated: 2023/10/04 10:46:15 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	if (argc > 1)
		return (ft_putstr_fd("Minishell: Error: too many arguments", 2), 1);
	prompt_loop(envp);
	return (0);
}
