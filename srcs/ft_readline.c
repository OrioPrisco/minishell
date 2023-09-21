/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:25:30 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/09/20 19:47:56 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include <readline/readline.h>
#include <stdlib.h>

t_ft_rl	*ft_rl_init(t_ft_rl *rlinfo)
{
	*rlinfo = (t_ft_rl){NULL, 0};
	return (rlinfo);
}

const char	*ft_readline(t_ft_rl *rlinfo, const char *prompt)
{
	if (!rlinfo->line || !rlinfo->line[rlinfo->offset])
	{
		rlinfo->offset = 0;
		free(rlinfo->line);
		rlinfo->line = readline(prompt);
	}
	if (!rlinfo->line)
		return (NULL);
	return (rlinfo->line + rlinfo->offset);
}

void	ft_rl_add_offset(t_ft_rl *rlinfo, size_t offset)
{
	rlinfo->offset += offset;
}

void	ft_rl_clear(t_ft_rl *rlinfo)
{
	free(rlinfo->line);
	*rlinfo = (t_ft_rl){NULL, 0};
}
