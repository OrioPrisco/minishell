/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringview.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:20:32 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/06/29 15:22:10 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGVIEW_H
# define STRINGVIEW_H

# include <stddef.h>

typedef struct s_stringview {
	const char	*start;
	size_t		size;
}	t_stringview;

#endif
