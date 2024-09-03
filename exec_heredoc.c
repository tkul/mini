/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:45:08 by tkul              #+#    #+#             */
/*   Updated: 2024/09/03 15:16:17 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc(t_token *token, t_exec **exec, int j)
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

void	ft_run_heredoc_without_cmd(t_token *token, t_exec **exec, int i)
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

void	ft_init_here_docs(t_data *data, t_exec **exec, int i, t_token *token)
{
	if (data->cmd_amount == 0)
		ft_run_heredoc_without_cmd(token, exec, i);
	if (exec[i]->is_here_doc)
		ft_heredoc(token, exec, i);
}
