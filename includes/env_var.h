/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 22:10:31 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/09/08 02:50:36 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_VAR_H
# define ENV_VAR_H

# include <stddef.h>

const char	*get_env_var(char **envp, const char *name, size_t name_size);
const char	*get_env_varnul(char **envp, const char *name, size_t name_size);

#endif
