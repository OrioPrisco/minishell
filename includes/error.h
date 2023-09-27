/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:59:31 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/09/26 17:37:18 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef struct s_cominfo	t_cominfo;

typedef enum e_error {
	SUCCESS = 0,
	PARSE_ERROR = 2,
	MALLOC_ERROR = 1,
	IS_A_DIRECTORY = 126,
	PERMISSION_NOT_GRANTED = 126,
	COMMAND_NOT_FOUND = 127,
	SIGINT_RECEIVED = 130,
}	t_error;

void	msh_error(const char *message);
void	msh_exit(t_cominfo *cominfo, int ret_code, int save_his);
void	access_error_print(const char *exec_name, t_cominfo *cominfo);
void	redirect_error_print(const char *filename);
#endif
