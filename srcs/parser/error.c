/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:30:19 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/10/02 16:30:31 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_int.h"
#include "tokens.h"
#include <unistd.h>
#include "ft_printf.h"
#include "ft_readline.h"
#include "libft.h"

static const t_tok_map_entry	g_token_map[] = {
{T_SPACE, " "},
{T_Q_START, "\'"},
{T_DQ_START, "\""},
{T_Q_END, "\'"},
{T_DQ_END, "\""},
{T_STR, "string"},
{T_END, "newline"},
{T_REDIRECT_STDOUT, ">"},
{T_REDIRECT_STDIN, "<"},
{T_HEREDOC, "<<"},
{T_REDIRECT_STDOUT_APPEND, ">>"},
{T_PIPE, "|"},
{T_VAR, "variable"},
{T_WILDCARD, "wildcard"},
{T_DIR_SEP, "/"},
{0, NULL},
};

static const char	*get_token_type_str(t_token_type token)
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

void	syntax_error(t_token_type type)
{
	ft_dprintf(2,
		"minishell: syntax error near unexpected token `%s'\n",
		get_token_type_str(type));
}
