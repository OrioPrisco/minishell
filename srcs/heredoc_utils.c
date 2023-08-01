/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:00:30 by dpentlan          #+#    #+#             */
/*   Updated: 2023/08/01 08:04:49 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include "vector.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>

/*
**	print_here_doc_contents
**	mostly for debugging purposes...
**	Will actually need to fork and dup after fork.
*/

int	print_here_doc_contents(int heredoc_fd)
{
	char buf[100];

	ft_bzero(buf, 100);
	// dup2(heredoc_fd, 0);
	// read(0, buf, 100);
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
	t_owned_token	*current;

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
	i = 0;
	return (0);
}

/*
**	here_doc_input_loop
**	
*/

int	here_doc_input_loop(int *pipefd, char *limiter)
{
	if (pipefd) {}
	if (limiter) {}
	return (0);
}

/*	
**	pipefd[0] = read end of the pipe
**	pipefd[1] = write end of the pipe
**	
**	Commenting out dup2 and close because when you dup the pipe to stdin, the 
	program continues and whatever is in the pipe gets dumped into the shell.
	Rather, you need to catch the contents of the pipe and send it to your program.
**	RETURN
**		-1 on error; int fd of pipe read end containing heredoc contents on success.
**/

int	check_and_open_heredoc(t_vector *tokens, int start, int stop)
{
	int			ret;
	char		*limiter;
	int			pipefd[2];
	char		*stdin_line;
	int			old_fd;

	old_fd = 0;
	ret = 0;
	limiter = 0;
	pipefd[0] = 0;
	pipefd[1] = 0;
	ret = check_for_heredoc(tokens, start, stop);
	while (ret)
	{
		if (pipefd[0])
			old_fd = pipefd[0];
		//limiter = ft_strjoin(((t_owned_token *)tokens->data + (ret + 1))->str, "\n");
		limiter = ((t_owned_token *)tokens->data + (ret + 1))->str;
		if (pipe(pipefd))
			return (perror("pipe"), -1);
		//here_doc_input_loop(pipefd, limiter);
		while (1)
		{
			stdin_line = 0;
			stdin_line = readline("heredoc> ");
			if (!stdin_line)
				return (close(pipefd[1]), -1);
			//ft_printf("stdin_line = %d, limiter = %d\n", ft_strlen(stdin_line), ft_strlen(limiter));
			if (!ft_strncmp(stdin_line, limiter, ft_strlen(limiter))
				&& ft_strlen(stdin_line) == ft_strlen(limiter))
			{
				free(stdin_line);
				break ;
			}
			ft_putstr_fd(stdin_line, pipefd[1]);
			free(stdin_line);
		}
		if (old_fd)
			close(old_fd);
		close(pipefd[1]);
		//free(limiter);
		ret = check_for_heredoc(tokens, start, stop);
	}
	return (pipefd[0]);
}
