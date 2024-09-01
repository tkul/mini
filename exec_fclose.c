/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fclose.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 02:39:39 by tkul              #+#    #+#             */
/*   Updated: 2024/09/01 14:52:26 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_close_for_fisrst_pipe(t_exec *exec, int *pipes, int i)
{
	if ((exec->in_file || exec->is_here_doc) && exec->out_fd)
	{
		close(exec->in_fd);
		close(exec->out_fd);
	}
	else if (exec->in_file || exec->is_here_doc)
	{
		close(exec->in_fd);
		close(pipes[i * 2 + 1]);
	}
	else if (exec->out_fd)
		close(exec->out_fd);
}

static void	ft_close_for_last_pipe(t_exec *exec, int *pipes, int i)
{
	if ((exec->in_file || exec->is_here_doc) && exec->out_fd)
	{
		close(exec->in_fd);
		close(exec->out_fd);
	}
	else if (exec->in_file || exec->is_here_doc)
		close(exec->in_fd);
	else if (exec->out_fd)
	{
		close(exec->out_fd);
		close(pipes[(i - 1) * 2]);
	}
}

static void	ft_close_for_middle_pipe(t_exec *exec, int *pipes, int i)
{
	if ((exec->in_file || exec->is_here_doc) && exec->out_fd)
	{
		close(exec->in_fd);
		close(exec->out_fd);
	}
	else if (exec->in_file || exec->is_here_doc)
	{
		close(exec->in_fd);
		close(pipes[i * 2 + 1]);
	}
	else if (exec->out_fd)
	{
		close(exec->out_fd);
		close(pipes[(i - 1) * 2]);
	}
}

int	close_redir_pipe_fd(t_data *data, t_exec *exec, int i)
{
	if (i == 0)
		ft_close_for_fisrst_pipe(exec, data->pipes, i);
	else if (i == data->cmd_amount - 1)
		ft_close_for_last_pipe(exec, data->pipes, i);
	else
		ft_close_for_middle_pipe(exec, data->pipes, i);
	return (0);
}

void	close_redir_fd(t_data *data, t_exec *exec, int fd1, int fd2)
{
	if (exec->in_fd)
		close(exec->in_fd);
	if (exec->out_fd)
		close(exec->out_fd);
	if (data->check > 0)
	{
		dup2(fd1, 1);
		dup2(fd2, 0);
	}
	if (data->check > 0)
	{
		close(fd1);
		close(fd2);
	}
}