/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:27:24 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/09/05 18:28:43 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "vector.h"
#include "ft_printf.h"

// munches some tokens and appends an owned_token to dest
//  returns 0  in case of malloc error (munching 0 tokens is nonsensical)
//  returns -1 in case of parsing error and prints an error message
//  returns the number of munched tokens on success
// could theoritcally use an array of function pointers,
//  but there are gaps in the token_type enum
static int	process_one_token(t_vector *dest, const t_token *tok, char **envp)
{
	if (tok->type == T_SPACE)
		return (1);
	if (is_redirect_type(tok->type))
		return (parse_redirect(dest, tok, envp)); // pass hd_line for heredocs
	if (tok->type == T_PIPE)
		return (parse_pipe(dest, tok));
	if (is_text_type(tok->type))
		return (parse_text(dest, tok, envp));
	ft_dprintf(2, "No muncher for type %s\n", token_type_to_str(tok->type));
	return (-1);
}

//parses a line into a vector of owned tokens
//will initialize the vector
//returns  1 on malloc error and free the vector
//returns -1 on parsing error, frees the vector, and prints an error to stderr
//returns  0 on success, and the vector will be populated
int	parse_line(const char *line, t_vector *dest, char **envp)
{
	t_vector	vec_token;
	t_token		*token;
	int			consumed;
	//char		*hd_line

	vector_init(&vec_token, sizeof(t_token));
	vector_init(dest, sizeof(t_owned_token));
	// rework to make it not choke on newline
	// have it return a pointer to where the parsing stopped for hd_line
	if (split_to_tokens(line, &vec_token)) 
		return (vector_clear(&vec_token), 1);
	token = vec_token.data;
	consumed = 0;
	while (token->type != T_END)
	{
		// need to pass envp for vars...
		consumed = process_one_token(dest, token, envp); // also pass hd_line for heredocs
		if (consumed <= 0) // consuming 0 tokens should means parsing error, what else could it mean
			return (vector_clear(&vec_token), vector_clear(dest),
				(consumed == -1) - (consumed == 0));
		token += consumed;
	}
	return (vector_clear(&vec_token), 0);
}
