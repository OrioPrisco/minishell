/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 22:52:36 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/07/14 16:43:03 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "vector.h"
#include "libft.h"
#include "env_var.h"

//expands all variables tokens to the corresponding env var
void	expand_vars(t_vector *vec_token, char **envp)
{
	size_t	i;
	t_token	*token;

	i = 0;
	while (i < vec_token->size)
	{
		token = ((t_token *)vec_token->data) + i++;
		if (token->type != T_VAR)
			continue ;
		token->strview.start = get_env_var(envp,
				token->strview.start, token->strview.size);
		if (!token->strview.start)
			token->strview.start = "";
		token->strview.size = ft_strlen(token->strview.start);
	}
}
