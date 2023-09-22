/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:35:18 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/09/22 15:34:36 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// for vector_free
void	free_str(void *data);
void	table_free(char **table);
void	table_print(char **table);
// for vector comparisons
int		compare_str(void *a, void *b);

#endif
