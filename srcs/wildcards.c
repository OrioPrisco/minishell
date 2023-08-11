/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users.nor  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:29:42 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/08/11 14:27:00 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "vector.h"
#include "libft.h"
#include "path.h"
#include "wildcards.h"
#include "utils.h"

static bool	split_str_token(const char *str, t_vector *dest)
{
	t_token	token;

	while (*str)
	{
		if (*str == '/')
			token = (t_token){{str, 1}, T_DIR_SEP};
		else
			token = (t_token){{str, ft_strcspn(str, "/")}, T_STR};
		if (vector_append(dest, &token))
			return (1);
		str = token.strview.start + token.strview.size;
	}
	return (0);
}
// compiles owned tokens to a wildcard expression
// on success returns 0 and the vector will be initialized and filled
// on failre returns 1 and the vector will be cleared

bool	compile_wildcard_expr(const t_owned_token *src, t_vector *dest)
{
	t_token		token;

	vector_init(dest, sizeof(t_token));
	while (is_wildcard_expr_type(src->type))
	{
		if (src->type == T_WILDCARD)
		{
			token = (t_token){{"*", 1}, T_WILDCARD};
			if (vector_append(dest, &token))
				return (vector_clear(dest), 1);
		}
		else if (is_text_type(src->type))
			if (split_str_token(src->str, dest))
				return (vector_clear(dest), 1);
		src++;
	}
	token = (t_token){{NULL, 0}, T_END};
	if (vector_append(dest, &token))
		return (vector_clear(dest), 1);
	return (0);
}

//filename is full filename, while curr is what is left to match
static bool	match_subexpression(const t_token *token, const char *filename,
			const char *curr)
{
	if (token->type == T_END || token->type == T_DIR_SEP)
		return (!*curr);
	if (is_text_type(token->type))
	{
		if (!ft_strncmp(curr, token->strview.start, token->strview.size))
			return (match_subexpression
				(token + 1, filename, curr + token->strview.size));
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
static	bool	subexpression_matches(const t_token *expr, const char *cwd,
					const char *filename, t_vector *dest)
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
bool	expand_wildcard(const t_token *expr, const char *cwd, t_vector *dest)
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
