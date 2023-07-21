/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:33:01 by dpentlan          #+#    #+#             */
/*   Updated: 2023/07/21 16:21:11 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

void	free_owned_tokens(t_vector *owned_tokens)
{
	size_t			i;
	t_owned_token	*current;

	i = 0;
	while (i < owned_tokens->size)
	{
		current = (t_owned_token *)owned_tokens->data + i;
		free(current->str);
		i++;
	}
}

void	print_tokens(t_vector *owned_tokens)
{
	size_t			i;
	t_owned_token	*token;

	i = 0;
	while (i < owned_tokens->size)
	{
		token = ((t_owned_token *)owned_tokens->data) + i;
		printf("%s : %s\n", token_type_to_str(token->type), token->str);
		i++;
	}
}

void	print_relavent_tokens(t_vector *owned_tokens, int start, int stop)
{
	int				i;
	t_owned_token	*token;

	i = start;
	while (i < stop)
	{
		token = ((t_owned_token *)owned_tokens->data) + i;
		printf("%s : %s\n", token_type_to_str(token->type), token->str);
		i++;
	}
}
