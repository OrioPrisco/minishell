/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:47:40 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/10/01 19:23:41 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "vector.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include "env_var.h"
#include "tokens.h"
#include "parser_int.h"
#include "msh_signal.h"
#include <signal.h>
#include <stdlib.h>
#include "ft_printf.h"
#include <errno.h>

static char	*expand_env_var(const char *str, const t_env_ret *env_ret)
{
	t_vector	tokens;
	t_token		token;
	char		*merged;

	vector_init(&tokens, sizeof(t_token));
	while (*str && *str != '\n')
	{
		if (*str == '$')
			token = (t_token){{str, next_non_identifier(str) - str}, T_VAR};
		else
			token = (t_token){{str, ft_strcspn(str, "$\n")}, T_STR};
		str = token.strview.start + token.strview.size;
		if (vector_append(&tokens, &token))
			return (vector_clear(&tokens), NULL);
	}
	if (merge_tokens(&merged, tokens.data, tokens.size, env_ret))
		return (vector_clear(&tokens), NULL);
	return (vector_clear(&tokens), merged);
}

/*
**	here_doc_append
**	RETURN
**		 1 on malloc error
**		 0 on end (success)
**		 2 on continue
*/
static int	here_doc_append(int pipefd, t_rlinfo_com rlinfo_com,
				const char *limiter, size_t limiter_len)
{
	size_t		input_len;
	char		*expanded;
	const char	*str_input;

	str_input = rlinfo_com.rlinfo->line + rlinfo_com.rlinfo->offset;
	input_len = ft_strcspn(str_input, "\n");
	ft_rl_add_offset(rlinfo_com.rlinfo, input_len
		+ (str_input[input_len] == '\n'));
	if (!ft_strncmp(str_input, limiter, limiter_len))
		return (vector_append(rlinfo_com.command, "\n")
			|| vector_append_elems
			(rlinfo_com.command, str_input, input_len));
	expanded = expand_env_var(str_input, rlinfo_com.env_ret);
	if (!expanded)
		return (1);
	if (vector_append(rlinfo_com.command, "\n") || vector_append_elems
		(rlinfo_com.command, str_input, input_len))
		return (free(expanded), 1);
	errno = 0;
	if (write(pipefd, expanded, ft_strlen(expanded)) == -1
		|| write(pipefd, "\n", 1) == -1)
		return (free(expanded), (errno == EINTR) * 2 - (errno != EINTR));
	free(expanded);
	return (2);
}

static const char	*g_message1 = "minishell: warning: here-document at line ";
static const char	*g_message2 = " delimited by end-of-file (wanted `";

/*
**	here_doc_input_loop
**	RETURN
**		 1 on malloc error
**		-1 on parsing error
**		 0 on success
*/
static int	here_doc_input_loop(int pipefd, const char *limiter,
		t_rlinfo_com rlinfo_com)
{
	const char	*str_input;
	size_t		limiter_len;
	size_t		ret;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
		str_input = ft_readline(rlinfo_com.rlinfo, "heredoc> ");
		if (!str_input && g_sig_triggered != HD_SIGINT)
			return (ft_dprintf(2, "%s%d%s%s')\n",
					g_message1, 42, g_message2, limiter), 0);
		if (!str_input)
			return (-1);
		ret = here_doc_append(pipefd, rlinfo_com, limiter, limiter_len);
		if (ret != 2)
			return (ret);
	}
}

/*	
**	pipefd[0] = read end of the pipe
**	pipefd[1] = write end of the pipe
**	
**	Opens a pipe, and take input with here_doc_input_loop,
**	
**	RETURN
**		int fd of pipe read end containing heredoc contents on success.
		-2 on parsing error.
		-1 on malloc  error.
**/
// TODO : handle signals
int	open_heredoc(const char *limiter,
		t_rlinfo_com rlinfo_com)
{
	int			ret;
	int			pipefd[2];
	int			stdin_dup;

	ft_bzero((void *)pipefd, sizeof(pipefd));
	stdin_dup = dup(STDIN_FILENO);
	if (stdin_dup == -1)
		return (perror("dup"), -1);
	if (pipe(pipefd))
		return (close(stdin_dup), perror("pipe"), -1);
	if (signal_assign(SIGINT, sigint_handler_heredoc))
		return (close(stdin_dup), close(pipefd[0]), close(pipefd[1]), -1);
	ret = here_doc_input_loop(pipefd[1], limiter, rlinfo_com);
	close(pipefd[1]);
	if (ret != -1)
		signal_assign(SIGINT, sigint_handler_parent);
	dup2(stdin_dup, STDIN_FILENO);
	close(stdin_dup);
	if (ret == 1)
		return (close(pipefd[0]), perror("malloc"), -1);
	if (ret == -1)
		return (close(pipefd[0]), -2);
	if (vector_null_term(rlinfo_com.command))
		return (close(pipefd[0]), perror("malloc"), -1);
	return (pipefd[0]);
}
