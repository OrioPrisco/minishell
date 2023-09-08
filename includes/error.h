/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:59:31 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/09/08 13:02:03 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum e_error {
	PARSE_ERROR = 2,
	IS_A_DIRECTORY = 126,
	PERMISSION_NOT_GRANTED = 126,
	COMMAND_NOT_FOUND = 127,
}	t_error;

#endif
