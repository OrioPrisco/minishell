/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 18:43:42 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/08/15 21:47:59 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"
#include "vector.h"
#include "utils.h"
#include "tokens.h"

void	sort_wildcards(t_vector *vector)
{
	vector_sort(vector, compare_str);
}
