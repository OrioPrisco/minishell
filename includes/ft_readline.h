/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:21:31 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/10/01 18:59:42 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H

# include <stddef.h>

typedef struct s_ft_rl {
	char	*line;
	size_t	offset;
	size_t	line_no;
}	t_ft_rl;

typedef void	(*t_sighandler)(int);

t_ft_rl		*ft_rl_init(t_ft_rl *rlinfo);
// if read handler is 0x0, it will be interpreted as NULL rather than SIG_DFL
// not the case for restore handler
const char	*ft_readline(t_ft_rl *rlinfo, const char *prompt,
				t_sighandler read_handler, t_sighandler restore_handler);
void		ft_rl_add_offset(t_ft_rl *rlinfo, size_t offset);
void		ft_rl_clear(t_ft_rl *rlinfo);

#endif
