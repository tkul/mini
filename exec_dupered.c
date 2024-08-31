/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dupered.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 02:36:12 by tkul              #+#    #+#             */
/*   Updated: 2024/08/31 11:27:53 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_dup_redictions(t_exec *exec, t_data *data)
{
	if (data->cmd_amount == 1 && exec->in_file && exec->type == CMD_BUILTIN \
		&& exec->in_type != APP_RED)
		return (close(exec->in_fd), 0);
	if (exec->in_file && exec->in_type == IN_RED && !exec->is_here_doc)
	{
		dup2(exec->in_fd, 0);
	}
	else if (exec->in_file && !exec->is_here_doc)
		dup2(exec->in_fd, 0);
	if (exec->out_file)
		dup2(exec->out_fd, 1);
	if (exec->in_fd && exec->is_here_doc)
		dup2(exec->in_fd, 0);
	return (0);
}

static void	ft_init_dupes_first(t_exec *exec, t_data *data, int i)
{
	if ((exec->in_file || exec->is_here_doc) && exec->out_file)
		mother_close_pipes_all(data);
	else if (exec->in_file || exec->is_here_doc)
	{
		dup2(data->pipes[i * 2 + 1], 1);
		close_pipes_all(data->pipes, data->cmd_amount, i);
	}
	else if (exec->out_file)
		mother_close_pipes_all(data);
}

static void	ft_init_dupes_last(t_exec *exec, t_data *data, int i)
{
	if ((exec->in_file || exec->is_here_doc) && exec->out_file)
		mother_close_pipes_all(data);
	else if (exec->in_file || exec->is_here_doc)
		mother_close_pipes_all(data);
	else if (exec->out_file)
	{
		dup2(data->pipes[(i - 1) * 2], 0);
		close_pipes_all(data->pipes, data->cmd_amount, i);
	}
}

static void	ft_init_dupes_midd(t_exec *exec, t_data *data, int i)
{
	if ((exec->in_file || exec->is_here_doc) && exec->out_file)
		mother_close_pipes_all(data);
	else if (exec->in_file || exec->is_here_doc)
	{
		dup2(data->pipes[i * 2 + 1], 1);
		close_pipes_all(data->pipes, data->cmd_amount, i);
		close(data->pipes[(i - 1) * 2]);
	}
	else if (exec->out_file)
	{
		dup2(data->pipes[(i - 1) * 2], 0);
		close_pipes_all(data->pipes, data->cmd_amount, i);
		close(data->pipes[i * 2 + 1]);
	}
}

void	ft_init_dupes(t_data *data, t_exec *exec, int i)
{
	if (i == 0)
		ft_init_dupes_first(exec, data, i);
	else if (i == data->cmd_amount - 1)
		ft_init_dupes_last(exec, data, i);
	else
		ft_init_dupes_midd(exec, data, i);
}
