/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:14:32 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/09/22 12:15:07 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "libft.h"
#include "minishell.h"

static const t_tok_map_entry	g_token_map[] = {
{T_SPACE, "SPACE"},
{T_Q_START, "Q_START"},
{T_DQ_START, "DQ_START"},
{T_Q_END, "Q_END"},
{T_DQ_END, "DQ_END"},
{T_STR, "STR"},
{T_END, "END"},
{T_REDIRECT_STDOUT, ">"},
{T_REDIRECT_STDIN, "<"},
{T_HEREDOC, "<<"},
{T_REDIRECT_STDOUT_APPEND, ">>"},
{T_PIPE, "|"},
{T_VAR, "VAR"},
{T_WILDCARD, "*"},
{T_DIR_SEP, "/"},
{0, NULL},
};

const char	*token_type_to_str(t_token_type token)
{
	const t_tok_map_entry	*entry;

	entry = &g_token_map[0];
	while (entry->str)
	{
		if (entry->type == token)
			return (entry->str);
		entry++;
	}
	return ("UNKNOWN");
}

bool	is_textexpr_type(t_token_type type)
{
	return (0
		|| is_text_type(type)
		|| type == T_Q_START
		|| type == T_Q_END
		|| type == T_DQ_START
		|| type == T_DQ_END
	);
}

bool	is_redirect_type(t_token_type type)
{
	return (0
		|| type == T_REDIRECT_STDOUT
		|| type == T_REDIRECT_STDIN
		|| type == T_REDIRECT_STDOUT_APPEND
		|| type == T_HEREDOC
	);
}
