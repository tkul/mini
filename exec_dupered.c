/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dupered.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 02:36:12 by tkul              #+#    #+#             */
/*   Updated: 2024/08/28 18:56:27 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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