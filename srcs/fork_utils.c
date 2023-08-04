/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpentlan <dpentlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:46:45 by dpentlan          #+#    #+#             */
/*   Updated: 2023/08/04 14:30:27 by dpentlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include "vector.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"
#include "utils.h"

/*
**	msh_wait
**	
*/

int	msh_wait(t_vector *pids)
{
	while (pids->size > 0)
	{
		waitpid(*((int *)pids->data + pids->size), NULL, 0);
		vector_pop_n(pids, pids->size - 1, 1);
	}
	return (0);
}

int	print_execve_args(char **execve_com_args)
{
	int	i;

	i = 0;
	ft_printf("execve_com_args = [ ");
	while (execve_com_args[i])
	{
		ft_printf("%s ", execve_com_args[i]);
		i++;
	}
	ft_printf("]\n");
	return (0);
}

/*
**	NAME
		*dup_and_add_to_com_table
**	DESCRIPTION
		
**	RETURN
		
*/

char	**dup_and_add_to_com_table(char **execve_com_args, char *str)
{
	char	**new_table;
	size_t		tab_size;

	tab_size = 0;
	new_table = 0;
	while (execve_com_args[tab_size])
		tab_size++;
	new_table = (char **)malloc(sizeof(char *) * (tab_size + 2));
	if (!new_table)
		return (NULL);
	(void)str;
	ft_bzero((void *)new_table, sizeof(char *) * (tab_size + 2));
	ft_memcpy(new_table, execve_com_args, sizeof(char *) * tab_size);
	new_table[tab_size + 1] = str;
	return (table_free(execve_com_args), new_table);
}

char	**add_item_to_com_table(char **execve_com_args, char *str)
{
	if (!execve_com_args)
	{
		execve_com_args = (char **)malloc(sizeof(char *) * 2);
		if (!execve_com_args)
			return (NULL);
		ft_bzero((void *)execve_com_args, sizeof(char *) * 2);
		execve_com_args[0] = ft_strdup(str);
		if (!execve_com_args[0])
			return (NULL);
	}
	else
	{
		execve_com_args = dup_and_add_to_com_table(execve_com_args, str);
		if (!execve_com_args)
			return (table_free(execve_com_args), NULL);
	}
	return (execve_com_args);
}

/*
**	
**	check the token logic. here I'm adding 1 if < > >> << so that we skip over 
		certain words
		CHECK THESE CASES
*/

char	**construct_execve_args(t_com_segment com_seg, char **execve_com_args)
{
	t_owned_token	*token;

	token = (t_owned_token *)com_seg.tokens->data + com_seg.start;
	while (token->type != T_END && token->type != T_PIPE)
	{
		if (is_redirect_type(token->type))
			token ++;
		else if (token->type == T_STR)
		{
			execve_com_args = add_item_to_com_table(execve_com_args, token->str);
			if (!execve_com_args)
				return (0);
		}
		token++;
	}	
	return (execve_com_args);
}
