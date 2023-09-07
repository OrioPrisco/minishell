/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:33:01 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/06 20:30:25 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

void	free_owned_token(void *owned_token)
{
	t_owned_token	*current;

	current = (t_owned_token *)owned_token;
	free(current->str);
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

bool	is_text_type(t_token_type type)
{
	return (0
		|| type == T_STR
		|| type == T_VAR
		|| type == T_DIR_SEP
		|| type == T_WILDCARD
	);
}
