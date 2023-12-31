/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:27:24 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/09/29 12:56:02 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "vector.h"
#include "ft_printf.h"
#include "env_var.h"
#include "error.h"
#include "ft_readline.h"
#include "parser.h"
#include "parser_int.h"
#include "libft.h"
#include "msh_signal.h"
#include <stdlib.h>

// munches some tokens and appends an owned_token to dest
//  returns 0  in case of malloc error (munching 0 tokens is nonsensical)
//  returns -1 in case of parsing error and prints an error message
//  returns the number of munched tokens on success
// could theoritcally use an array of function pointers,
//  but there are gaps in the token_type enum
static int	process_one_token(t_vector *dest, const t_token *tok,
				t_rlinfo_com rlinfocom)
{
	if (tok->type == T_SPACE)
		return (1);
	if (is_redirect_type(tok->type))
		return (parse_redirect(dest, tok, rlinfocom));
	if (tok->type == T_PIPE)
		return (parse_pipe(dest, tok));
	if (is_textexpr_type(tok->type))
		return (parse_text(dest, tok, rlinfocom.env_ret, 0));
	ft_dprintf(2, "No muncher for type %s\n", token_type_to_str(tok->type));
	return (-1);
}

//parses a line into a vector of owned tokens
//will initialize the vector
//returns  1 on malloc error and free the vector
//returns -1 on parsing error, frees the vector, and prints an error to stderr
//returns  0 on success, and the vector will be populated
static int	parse_line_int(const char *line, t_vector *dest,
				t_rlinfo_com rlinfo_com)
{
	t_vector		vec_token;
	t_token			*token;
	int				consumed;
	t_owned_token	tok;

	vector_init(&vec_token, sizeof(t_token));
	if (split_to_tokens(line, &vec_token, rlinfo_com))
		return (vector_clear(&vec_token), 1);
	token = vec_token.data;
	consumed = 0;
	while (token->type != T_END)
	{
		consumed = process_one_token(dest, token, rlinfo_com);
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

bool	parse_line(char **parsed, t_vector *dest, t_env_ret *env_ret,
		t_ft_rl *rlinfo)
{
	int				ret;
	t_vector		command;
	t_rlinfo_com	rlinfo_com;
	char			*line_cpy;

	line_cpy = ft_strdup(rlinfo->line + rlinfo->offset);
	if (!line_cpy)
		return (1);
	g_sig_triggered = NONE;
	rlinfo_com = (t_rlinfo_com){rlinfo, &command, env_ret};
	vector_init(&command, sizeof(char));
	vector_init(dest, sizeof(t_owned_token));
	ret = parse_line_int(line_cpy, dest, rlinfo_com);
	if (dest->size == 1 && ((t_owned_token *)dest->data)[0].type == T_END)
		vector_free(dest, free_owned_token);
	else if (ret == -1 && g_sig_triggered != HD_SIGINT)
		env_ret->prev_ret = PARSE_ERROR;
	else if (g_sig_triggered == HD_SIGINT)
		env_ret->prev_ret = SIGINT_RECEIVED;
	if (ret == 1)
		vector_clear(&command);
	*parsed = vector_move_data(&command);
	return (free(line_cpy), ret == 1);
}
