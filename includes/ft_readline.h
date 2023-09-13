/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:21:31 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/09/13 15:27:04 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H

# define FT_READLINE_H

typedef struct s_ft_rl {
	char	*line;
	int		offset;
}	t_ft_rl;

t_ft_rl		*ft_rl_init(t_ft_rl *rlinfo);
const char	*ft_readline(t_ft_rl *rlinfo, const char *prompt);
void		ft_rl_set_offset(t_ft_rl *rlinfo, const char *end);
void		ft_rl_clear(t_ft_rl *rlinfo);

#endif
