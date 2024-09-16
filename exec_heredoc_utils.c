/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:00:46 by tkul              #+#    #+#             */
/*   Updated: 2024/09/05 12:25:20 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc_helper(t_token *token, t_exec *exec, char *buff)
{
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
			return (1);
		}
	}
	return (0);
}

void	ft_heredoc_helper2(t_data *data, int pipe_fd[2], char **buff,
		t_exec *exec)
{
	if (data->h_flag == exec->count_heredocs - 1)
		ft_heredoc_writer(data, pipe_fd, buff);
	if (*buff)
		free(*buff);
}

void	ft_heredoc_loop(t_data *data, t_token *token, t_exec *exec,
		int pipe_fd[2])
{
	char	*buff;

	data->h_flag = 0;
	buff = "init_value";
	while (buff && exec->count_heredocs > 0)
	{
		buff = readline("> ");
		if (ft_heredoc_helper(token, exec, buff))
			continue ;
		if (buff == NULL || !ft_strcmp(buff, exec->is_here_doc))
		{
			if (buff == NULL || data->h_flag == exec->count_heredocs - 1)
			{
				if (buff)
					free(buff);
				break ;
			}
			data->h_flag++;
			if (buff)
				free(buff);
			continue ;
		}
		ft_heredoc_helper2(data, pipe_fd, &buff, exec);
	}
}
