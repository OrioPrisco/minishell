/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:00:30 by dpentlan          #+#    #+#             */
/*   Updated: 2023/09/05 12:17:20 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include "vector.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include "libft.h"
#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>

/*
**	print_here_doc_contents
**	mostly for debugging purposes...
**	Will actually need to fork and dup after fork.

	// dup2(heredoc_fd, 0);
	// read(0, buf, 100);

*/

int	print_here_doc_contents(int heredoc_fd)
{
	char	buf[100];

	ft_bzero(buf, 100);
	read(heredoc_fd, buf, 100);
	write(1, buf, 100);
	write(1, "\n", 1);
	close(heredoc_fd);
	return (0);
}

/*
**	check_for_heredoc
**	
**	Using a static int so that we can iterate over then entire selection with 
	while loop in the calling function. Then when we do not find a token we can 
	reset i to 0 for the next command.
**	
*/

static int	check_for_heredoc(t_vector *tokens, int start, int stop)
{
	static int				i;
	t_owned_token			*current;

	while (i + start < stop)
	{
		current = (t_owned_token *)tokens->data + (i + start);
		if (current->type == T_HEREDOC)
		{
			i++;
			return (i + start - 1);
		}
		i++;
	}
	return (0);
}

/*
**	add_nl_to_com_list
**	
*/

bool	append_str_to_com_list(char *str, t_cominfo *cominfo)
{
	char	*swap;

	swap = 0;
	swap = cominfo->command;
	cominfo->command = ft_strjoin(swap, str);
	free(swap);
	if (!cominfo->command)
		return (1);
	return (0);
}

/*
**	here_doc_input_loop
**	
		// ft_putstr_fd(str_input, pipefd[1]);
		// ft_putstr_fd("\n", pipefd[1]);
*/

int	here_doc_input_loop(int *pipefd, char *limiter, t_cominfo *cominfo)
{
	char		*str_input;

	while (1)
	{
		str_input = 0;
		str_input = readline("heredoc> ");
		if (!str_input)
			return (close(pipefd[1]), close(pipefd[0]),
				msh_exit(cominfo), -1);
		if (append_str_to_com_list("\n", cominfo)
			|| append_str_to_com_list(str_input, cominfo))
			return (free(str_input), -1);
		if (!ft_strcmp(str_input, limiter))
			return (free(str_input), 0);
		ft_dprintf(pipefd[1], "%s\n", str_input);
		free(str_input);
	}
}

/*	
**	pipefd[0] = read end of the pipe
**	pipefd[1] = write end of the pipe
**	
**	Here we iterate over the command searching for heredoc tokens using
	check_for_heredoc
**	For each heredoc found, we open a pipe, take input with here_doc_input_loop,
	close, and restart.
**	
**	RETURN
**		int fd of pipe read end containing heredoc contents on success.
		-1 on error.
**/

int	check_and_open_heredoc(t_vector *tokens, int start, int stop,
						t_cominfo *cominfo)
{
	int			ret;
	char		*limiter;
	int			pipefd[2];
	int			old_fd;

	old_fd = 0;
	limiter = 0;
	ft_bzero((void *)pipefd, sizeof(pipefd));
	ret = check_for_heredoc(tokens, start, stop);
	while (ret)
	{
		if (pipefd[0])
			old_fd = pipefd[0];
		limiter = ((t_owned_token *)tokens->data + (ret + 1))->str;
		if (pipe(pipefd))
			return (perror("pipe"), -1);
		if (here_doc_input_loop(pipefd, limiter, cominfo))
			return (perror("malloc"), -1);
		if (old_fd)
			close(old_fd);
		close(pipefd[1]);
		ret = check_for_heredoc(tokens, start, stop);
	}
	return (pipefd[0]);
}
