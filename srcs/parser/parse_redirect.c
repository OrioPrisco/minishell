/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:07:23 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/09/04 14:59:43 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "vector.h"

// will need to take hd_line
// will need merge token function that takes const t_token and size_t
int	parse_redirect(t_vector *dest, const t_token *tok, char **envp)
{
	t_owned_token	token;

	(void)envp;
	token = (t_owned_token){NULL, tok->type};
	if (tok->type == T_HEREDOC)
	{
		// merge the next tokens into text and call the heredoc function
	}
	else {} //check that there is a text token after an eventual space or error (need to expand vars)
	// could possibly put the filename in the redir token here
	if (vector_append(dest, &tok))
		return (0);
	return (1);
}
