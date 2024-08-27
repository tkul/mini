/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:45:08 by tkul              #+#    #+#             */
/*   Updated: 2024/08/27 12:25:08 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_heredoc_writer(int pipe_fd[2], char *buff)
{
	write(pipe_fd[1], buff, ft_strlen(buff));
	write(pipe_fd[1], "\n", 1);
}

void	ft_heredoc_loop(t_token *token, t_exec *exec, char *buff, int pipe_fd[2])
{
	int	i;

	i = 0;
	while (buff)
	{
		buff = readline("> ");
		if (exec->count_heredocs > 1)
		{
			if (!ft_strcmp(buff, exec->is_here_doc))
			{
				free(buff);
				while(token)
				{
					if (!ft_strcmp(token->value, exec->is_here_doc))
						break ;
					token = token->next;
				}
				exec->is_here_doc = ft_is_here_doc2(exec,token);
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
	}
}


void	ft_heredoc(t_token *token, t_exec **exec , int j)
{
	int		pipe_fd[2];
	char	*buff;

	buff = "init_value";
	if (pipe(pipe_fd) == -1)
		return ;
	ft_heredoc_loop(token, exec[j], buff, pipe_fd);
	close(pipe_fd[1]);
	exec[j]->in_fd = pipe_fd[0];
}


void	ft_run_heredoc_without_cmd(t_token *token,t_exec **exec, int i)
{
	int		pipe_fd[2];
	char	*buff;

	buff = "init_value";
	if (pipe(pipe_fd) == -1)
		return ;
	ft_heredoc_loop(token, exec[i], buff, pipe_fd);
	close(pipe_fd[1]);
	exec[i]->in_fd = pipe_fd[0];
}

void	ft_init_here_docs(t_data *data, t_exec **exec, int i)
{
	int	j;
	t_token *token;

	j = -1;
	token = data->tokens[i];
	if (data->cmd_amount == 0)
		ft_run_heredoc_without_cmd(token, exec, i);
	while (++j < data->cmd_amount)
	{
		if (exec[j]->is_here_doc)
			ft_heredoc(token, exec, j);
	}
}
