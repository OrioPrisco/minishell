/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:29:42 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/09/29 13:48:54 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "vector.h"
#include "libft.h"
#include "path.h"
#include "wildcards.h"
#include "utils.h"
#include <stdlib.h>
#include "env_var.h"
#include "parser_int.h"

// 0 means malloc error
// returns tokens munched
static int	merge_text(const t_token *src, char **dest,
	int to_merge)
{
	t_vector	sbuilder;
	int			max_merge;

	max_merge = to_merge;
	vector_init(&sbuilder, sizeof(char));
	while (to_merge && src->type != T_WILDCARD && src->type != T_DIR_SEP)
	{
		if (src->type == T_STR)
			if (vector_append_elems(&sbuilder,
					src->strview.start, src->strview.size))
				return (vector_clear(&sbuilder), 0);
		src++;
		to_merge--;
	}
	if (sbuilder.size == 0)
		return (*dest = NULL, max_merge - to_merge);
	if (vector_null_term(&sbuilder))
		return (vector_clear(&sbuilder), 0);
	*dest = vector_move_data(&sbuilder);
	return (max_merge - to_merge);
}

// compiles tokens to a wildcard expression (owned_tokens)
// on success returns 0 and the vector will be initialized and filled
// on failre returns 1 and the vector will be cleared
// returns 0 on sucess
// returns 1 on error
bool	compile_wildcard_expr(const t_token *src, t_vector *dest,
			int to_merge)
{
	t_owned_token	token;
	int				merged;
	int				ret;

	merged = src->type == T_SPACE;
	vector_init(dest, sizeof(t_owned_token));
	while (merged < to_merge)
	{
		token = (t_owned_token){NULL, T_STR, 0};
		if (src[merged].type != T_WILDCARD && src[merged].type != T_DIR_SEP)
		{
			ret = merge_text(src + merged, &token.str, to_merge - merged);
			if (ret == 0)
				return (0);
			merged += ret;
		}
		else
			token = (t_owned_token){NULL, src[merged++].type, 0};
		if ((token.type != T_STR || token.str) && vector_append(dest, &token))
			return (vector_free(dest, free_owned_token), 1);
	}
	token = (t_owned_token){NULL, T_END, 0};
	if (vector_append(dest, &token))
		return (vector_free(dest, free_owned_token), 1);
	return (0);
}

//filename is full filename, while curr is what is left to match
static bool	match_subexpression(const t_owned_token *token,
			const char *filename, const char *curr)
{
	size_t	len;

	if (token->type == T_END || token->type == T_DIR_SEP)
		return (!*curr);
	if (token->type == T_STR)
	{
		len = ft_strlen(token->str);
		if (!ft_strncmp(curr, token->str, len))
			return (match_subexpression(token + 1, filename, curr + len));
		return (0);
	}
	if (token->type != T_WILDCARD
		|| (*filename == '.' && filename == curr))
		return (0);
	while (*curr)
		if (match_subexpression(token + 1, filename, curr++))
			return (1);
	return (match_subexpression(token + 1, filename, curr));
}

// helper for expand wildcard
// vector must be initialized, results are char *
// returns 0 on success and the vector will be populated
// return 1 error and the vector will be cleared
static	bool	subexpression_matches(const t_owned_token *expr,
					const char *cwd, const char *filename, t_vector *dest)
{
	char	*path;
	char	*temp;

	while (expr->type != T_DIR_SEP && expr->type != T_END)
		expr++;
	path = path_concat(cwd, filename);
	if (!path)
		return (1);
	if (expr->type == T_DIR_SEP)
	{
		temp = path_concat(path, "");
		free(path);
		if (!temp)
			return (1);
		path = temp;
		expr += 1;
		if (is_directory(path) <= 0)
			return (free(path), 0);
		if (expr->type != T_END && (expand_wildcard(expr, path, dest)
				|| (free(path), 0)))
			return (free(path), 1);
	}
	if (expr->type == T_END && vector_append(dest, &path))
		return (free(path), 1);
	return (0);
}

// takes a wildcard expression and returns a vector of all matches
// vector must be initialized, results are char *
// returns 0 on success and the vector will be populated
// return 1 error and the vector will NOT be cleared
bool	expand_wildcard(const t_owned_token *expr, const char *cwd,
			t_vector *dest)
{
	t_vector	files;
	int			res;
	size_t		i;
	const char	*filename;

	vector_init(&files, sizeof(char *));
	if (*cwd)
		res = get_dir_files(&files, cwd);
	else
		res = get_dir_files(&files, ".");
	if (res != 0)
		return (res > 0);
	i = 0;
	while (i < files.size)
	{
		filename = ((char **)files.data)[i++];
		if (match_subexpression(expr, filename, filename)
			&& subexpression_matches(expr, cwd, filename, dest))
			return (vector_free(&files, free_str), 1);
	}
	return (vector_free(&files, free_str), 0);
}
