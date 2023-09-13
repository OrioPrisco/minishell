/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:27:24 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/09/13 17:04:12 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "vector.h"
#include "ft_printf.h"
#include "env_var.h"
#include "error.h"
#include "ft_readline.h"

// munches some tokens and appends an owned_token to dest
//  returns 0  in case of malloc error (munching 0 tokens is nonsensical)
//  returns -1 in case of parsing error and prints an error message
//  returns the number of munched tokens on success
// could theoritcally use an array of function pointers,
//  but there are gaps in the token_type enum
static int	process_one_token(t_vector *dest, const t_token *tok,
				const t_env_ret *env_ret, t_ft_rl *rlinfo)
{
	if (tok->type == T_SPACE)
		return (1);
	if (is_redirect_type(tok->type))
		return (parse_redirect(dest, tok, env_ret, rlinfo));
	if (tok->type == T_PIPE)
		return (parse_pipe(dest, tok));
	if (is_textexpr_type(tok->type))
		return (parse_text(dest, tok, env_ret));
	ft_dprintf(2, "No muncher for type %s\n", token_type_to_str(tok->type));
	return (-1);
}

//parses a line into a vector of owned tokens
//will initialize the vector
//returns  1 on malloc error and free the vector
//returns -1 on parsing error, frees the vector, and prints an error to stderr
//returns  0 on success, and the vector will be populated
static int	parse_line_int(const char *line, t_vector *dest,
				const t_env_ret *env_ret, t_ft_rl *rlinfo)
{
	t_vector		vec_token;
	t_token			*token;
	int				consumed;
	t_owned_token	tok;
	const char		*hd_line;

	vector_init(&vec_token, sizeof(t_token));
	vector_init(dest, sizeof(t_owned_token));
	if (split_to_tokens(line, &vec_token, &hd_line))
		return (vector_clear(&vec_token), 1);
	ft_rl_set_offset(rlinfo, hd_line);
	token = vec_token.data;
	consumed = 0;
	while (token->type != T_END)
	{
		consumed = process_one_token(dest, token, env_ret, rlinfo);
		if (consumed <= 0)
			return (vector_clear(&vec_token), vector_free(dest,
					free_owned_token), consumed);
		token += consumed;
	}
	tok = (t_owned_token){NULL, T_END, 0};
	if (vector_append(dest, &tok))
		return (vector_clear(&vec_token),
			vector_free(dest, free_owned_token), 1);
	return (vector_clear(&vec_token), 0);
}

int	parse_line(const char *line, t_vector *dest, t_env_ret *env_ret,
		t_ft_rl *rlinfo)
{
	int	ret;

	ret = parse_line_int(line, dest, env_ret, rlinfo);
	if (ret == -1)
		env_ret->prev_ret = PARSE_ERROR;
	else
		env_ret->prev_ret = 0;
	return (ret);
}
