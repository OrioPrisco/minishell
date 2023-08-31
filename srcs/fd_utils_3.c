/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:17:49 by dpentlan          #+#    #+#             */
/*   Updated: 2023/08/31 15:32:55 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"

/*
	NAME
		char	*find_fn_for_stdout_token
	DESCRIPTION
		
	RETURN
		
*/

char	*find_fn_for_stdout_token(t_owned_token *owned_token)
{
	while (!owned_token->str)
		owned_token = owned_token + 1;
	return (owned_token->str);
}
