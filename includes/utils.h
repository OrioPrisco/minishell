/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:35:18 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/08/08 16:36:38 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	free_str(void *data);
void	table_free(char **table);
void	table_print(char **table);
int		is_directory(const char *filename);

#endif
