/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:00:46 by tkul              #+#    #+#             */
/*   Updated: 2024/09/03 00:18:45 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc_writer(int pipe_fd[2], char *buff)
{
	write(pipe_fd[1], buff, ft_strlen(buff));
	write(pipe_fd[1], "\n", 1);
}

void	ft_heredoc_loop(t_token *token, t_exec *exec, char *buff,
		int pipe_fd[2])
{
	int	i;

	i = 0;
	while (buff && exec->count_heredocs > 0)
	{
		buff = readline("> ");
		if (exec->count_heredocs > 1)
		{
			if (!ft_strcmp(buff, exec->is_here_doc))
			{
				free(buff);
				while (token)
				{
					if (!ft_strcmp(token->value, exec->is_here_doc))
						break ;
					token = token->next;
				}
				exec->is_here_doc = ft_is_here_doc2(exec, token);
				exec->count_heredocs--;
				i = 0;
				continue ;
			}
		}
		if (buff == NULL || !ft_strcmp(buff, exec->is_here_doc))
		{
			if (buff == NULL || i == exec->count_heredocs - 1)
			{
				if (buff)
					free(buff);
				break ;
			}
			i++;
			if (buff)
				free(buff);
			continue ;
		}
		if (i == exec->count_heredocs - 1)
			ft_heredoc_writer(pipe_fd, buff);
		free(buff);
	}
}
