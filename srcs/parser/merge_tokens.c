/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:22:52 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/10/02 16:36:38 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "vector.h"
#include "env_var.h"
#include "libft.h"
#include "ft_printf.h"
#include "parser_int.h"

// seeks the end/space token and make sure there are no unterminated (d)quote
// returns -1 on parse error
// returns number of tokens until space/end otherwise
// skips the first token if it is a space
int	seek_tokens_to_merge(const t_token *src)
{
	t_state	state;
	int		to_munch;

	state = NORMAL;
	to_munch = src->type == T_SPACE;
	if (src->type == T_SPACE)
		src++;
	while (is_textexpr_type(src->type))
	{
		if (src->type == T_DQ_START)
			state = DQUOTE;
		else if (src->type == T_Q_START)
			state = QUOTE;
		else if (src->type == T_DQ_END || src->type == T_Q_END)
			state = NORMAL;
		to_munch++;
		src++;
	}
	if (state != NORMAL)
	{
		syntax_error(T_END);
		return (-1);
	}
	return (to_munch);
}

static int	merge_one_token(t_vector *sbuilder, const t_token *src,
				const t_env_ret *env_ret)
{
	const char	*env_var;

	if (env_ret && src->type == T_VAR)
	{
		env_var = get_env_varnul(env_ret, src->strview.start,
				src->strview.size);
		if (vector_append_elems(sbuilder, env_var, ft_strlen(env_var)))
			return (1);
	}
	else if (is_text_type(src->type))
		if (vector_append_elems(sbuilder,
				src->strview.start, src->strview.size))
			return (1);
	return (0);
}

//make two separate functions ?
//one would seek how many tokens to merge, and stop on space
// would also error out if a (d)quote is not closed
// the other would just merge

// returns 1 on malloc error
// pass NULL as envp to prevent var expansion
// completely trusts that to_merge is correct
// skips the first token if it is a space
bool	merge_tokens(char **dest, const t_token *src, size_t to_merge,
		const t_env_ret *env_ret)
{
	t_vector	sbuilder;

	if (to_merge && src->type == T_SPACE)
	{
		src++;
		to_merge--;
	}
	vector_init(&sbuilder, sizeof(char));
	while (to_merge && src->type != T_END && src->type != T_SPACE)
	{
		if (merge_one_token(&sbuilder, src, env_ret))
			return (vector_clear(&sbuilder), 1);
		to_merge--;
		src++;
	}
	if (vector_null_term(&sbuilder))
		return (vector_clear(&sbuilder), 1);
	*dest = vector_move_data(&sbuilder);
	return (0);
}
