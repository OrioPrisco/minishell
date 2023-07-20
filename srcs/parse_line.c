/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:27:24 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/07/19 16:12:39 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "vector.h"

static bool	process_tokens(t_vector	*vector)
{
	t_token	*token;

	token = vector->data;
	while (token->type != T_END)
		if (process_one_token(token++))
			return (1);
	return (0);
}

//parses a line into a vector of owned tokens
//will initialize the vector
//returns 1 on error and free the vector
//returns 0 on success, and the vector will be populated
bool	parse_line(const char *line, t_vector *dest, char **envp)
{
	t_vector	vec_token;

	vector_init(&vec_token, sizeof(t_token));
	if (0
		|| split_to_tokens(line, &vec_token)
		|| process_tokens(&vec_token)
		|| split_dquoted_tokens(&vec_token)
		|| (expand_vars(&vec_token, envp), 0)
		|| merge_tokens(dest, &vec_token))
		return (vector_clear(&vec_token), 1);
	return (vector_clear(&vec_token), 0);
}
