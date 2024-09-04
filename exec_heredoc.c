/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:45:08 by tkul              #+#    #+#             */
/*   Updated: 2024/09/04 10:01:01 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc(t_data *data, t_token *token, t_exec **exec, int j)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return ;
	ft_heredoc_loop(data, token, exec[j], pipe_fd);
	close(pipe_fd[1]);
	exec[j]->in_fd = pipe_fd[0];
}

void	ft_run_heredoc_without_cmd(t_data *data, t_token *token, t_exec **exec,
		int i)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return ;
	ft_heredoc_loop(data, token, exec[i], pipe_fd);
	close(pipe_fd[1]);
	exec[i]->in_fd = pipe_fd[0];
}

void	ft_init_here_docs(t_data *data, t_exec **exec, int i, t_token *token)
{
	if (data->cmd_amount == 0)
		ft_run_heredoc_without_cmd(data, token, exec, i);
	if (exec[i]->is_here_doc)
		ft_heredoc(data, token, exec, i);
}
