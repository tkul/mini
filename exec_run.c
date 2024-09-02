/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 11:30:41 by tkul              #+#    #+#             */
/*   Updated: 2024/09/02 17:36:25 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_run_exec(t_data *data, t_token *token, int i, t_exec *exec)
{
	close_pipes_all(data->pipes, data->cmd_amount, i);
	if (data->check > 0)
	{
		ft_run_builtin(data, i, token, exec);
		exit(data->status);
	}
	ft_set_path(data, token, exec);
	if (data->path == NULL)
		exit(data->status);
	ft_set_args(data, token);
	if (execve(data->path, data->args, data->env) == -1)
		exit(1);
}

void	ft_run_commands(t_data *data, t_token *token, int i, t_exec *exec)
{
	if (i == 0)
	{
		dup2(data->pipes[i * 2 + 1], 1);
		ft_run_exec(data, token, i, exec);
	}
	else if (i == data->cmd_amount - 1)
	{
		dup2(data->pipes[(i - 1) * 2], 0);
		ft_run_exec(data, token, i, exec);
	}
	else
	{
		dup2(data->pipes[(i - 1) * 2], 0);
		dup2(data->pipes[i * 2 + 1], 1);
		ft_run_exec(data, token, i, exec);
	}
}

void	ft_run_pipes(t_data *data, t_exec *exec, int i, t_token *token)
{
	if (exec->type == CMD_WITHOUT_CMD)
	{
		mother_close_pipes_all(data);
		exit(0);
	}
	else if (exec->should_run)
	{
		mother_close_pipes_all(data);
		exit(1);
	}
	else if (!exec->in_type && !exec->out_type && !exec->is_here_doc)
		ft_run_commands(data, token, i, exec);
	else
		ft_run_redirects(data, token, exec, i);
}
