/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:59:31 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/09/19 14:51:08 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum e_error {
	SUCCESS = 0,
	PARSE_ERROR = 2,
	MALLOC_ERROR = 1,
	IS_A_DIRECTORY = 126,
	PERMISSION_NOT_GRANTED = 126,
	COMMAND_NOT_FOUND = 127,
	HEREDOC_EXITED = 130,
}	t_error;

#endif
