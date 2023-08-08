/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:02:35 by dpentlan          #+#    #+#             */
/*   Updated: 2023/08/08 16:33:43 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

void	print_access_debug(char *execve_command)
{
	if (!execve_command[0])
		ft_printf("no access found\n");
	else
		ft_printf("access found\n");
}
