/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:47:40 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/09/18 16:06:51 by OrioPrisc        ###   ########.fr       */
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

/*
**	here_doc_input_loop
**	
*/
// TODO : substitute env vars
static int	here_doc_input_loop(int pipefd, const char *limiter,
		const t_env_ret *env_ret, t_rlinfo_com rlinfo_com)
{
	const char	*str_input;
	size_t		input_len;

	while (1)
	{
		str_input = ft_readline(rlinfo_com.rlinfo, "heredoc> ");
		if (!str_input)
			return (-1);
		input_len = ft_strcspn(str_input, "\n");
		ft_rl_set_offset(rlinfo_com.rlinfo, str_input + input_len
			+ (str_input[input_len] == '\n'));
		(void)env_ret;
		if (vector_append(rlinfo_com.command, "\n")
			|| vector_append_elems(rlinfo_com.command, str_input, input_len))
			return (1);
		if (!ft_strncmp(str_input, limiter, input_len))
			return (0);
		write(pipefd, str_input, ft_strcspn(str_input, "\n"));
		write(pipefd, "\n", 1);
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
int	open_heredoc(const char *limiter, const t_env_ret *env_ret,
		t_rlinfo_com rlinfo_com)
{
	int			ret;
	int			pipefd[2];

	ft_bzero((void *)pipefd, sizeof(pipefd));
	if (pipe(pipefd))
		return (perror("pipe"), -2);
	ret = here_doc_input_loop(pipefd[1], limiter, env_ret, rlinfo_com);
	if (ret == 1)
		return (close(pipefd[1]), close(pipefd[0]), perror("malloc"), -1);
	if (ret == -1)
		return (close(pipefd[1]), close(pipefd[0]), -2);
	if (vector_null_term(rlinfo_com.command))
		return (close(pipefd[1]), close(pipefd[0]), perror("malloc"), -1);
	close(pipefd[1]);
	return (pipefd[0]);
}
