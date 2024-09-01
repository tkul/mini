/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 23:46:21 by tkul              #+#    #+#             */
/*   Updated: 2024/09/01 14:12:09 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_part(t_data *data, t_exec *exec, t_token *token)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		ft_run_pipes(data, exec, data->index, token);
	data->forks[data->index] = pid;
}

static void	ft_wait_part(t_data *data)
{
	int	i;

	i = data->cmd_amount - 1;
	while (i >= 0)
	{
		if (i == data->cmd_amount - 1)
		{
			waitpid(data->forks[i], &data->status, 0);
			if (WIFEXITED(data->status))
				data->status = WEXITSTATUS(data->status);
		}
		waitpid(data->forks[i], NULL, 0);
		i--;
	}
}

void	ft_start_exec(t_data *data, t_exec **exec, t_token *token, int i)
{
	int		err;
	t_token	*tmp;

	err = 0;
	tmp = token;
	ft_init_here_docs(data, exec, i, token);
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			if (!exec[i]->type)
				exec[i]->type = ft_find_exec_type(exec, token, i);
		}
		tmp = tmp->next;
	}
	err = ft_exec_init_redirection(data, exec[i], token);
	if (err)
		return(ft_set_exec_err(data, exec[i], err, token->value));
	g_qsignal = 1;
	if (data->cmd_amount > 1)
	{
		if (token->type == CMD || exec[i]->type == CMD_WITHOUT_CMD)
			ft_exec_part(data, exec[data->index], token);
	}
	else
		ft_run_single_cmd(data, exec, i, token);
	g_qsignal = 0;
}

void	free_exec_data(t_data *data, t_exec **exec, int cmd_amount)
{
	int	i;

	i = 0;
	while (i < cmd_amount)
	{
		if (exec[i]->is_here_doc)
		{
			free(exec[i]->is_here_doc);
			exec[i]->is_here_doc = NULL;
		}
		if (exec[i]->out_file)
		{
			free(exec[i]->out_file);
			exec[i]->out_file = NULL;
		}
		if (exec[i]->in_file)
		{
			free(exec[i]->in_file);
			exec[i]->in_file = NULL;
		}
		free(exec[i]);
		exec[i] = NULL;
		i++;
	}
	if (data->path)
	{
		free(data->path);
		data->path = NULL;
	}
	if (data->args)
	{
		ft_free_array(data->args);
		data->args = NULL;
	}
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
	if (data->pipes)
	{
		free(data->pipes);
		data->pipes = NULL;
	}
}

void	ft_execute(t_data *data)
{
	t_exec	**exec;
	t_token	*token;
	int		i;

	i = 0;
	data->index = 0;
	data->cmd_amount = ft_count_cmds(data->tokens);
	if (data->cmd_amount < 0)
		return ;
	exec = malloc(sizeof(t_exec *) * (data->cmd_amount + 1));
	exec[data->cmd_amount] = NULL;
	while (i < data->cmd_amount)
	{
		exec[i] = malloc(sizeof(t_exec));
		ft_init_exec(data, exec[i], data->tokens[i]);
		i++;
	}
	ft_init_pipes(data);
	i = 0;
	while (data->tokens[i])
	{
		data->index = i;
		token = data->tokens[i];
		data->check = ft_is_builtins(token->value);
		ft_start_exec(data, exec, token, data->index);
		i++;
	}
	ft_print_exec_errors(data, exec);
	if (!(data->check > 0 && data->cmd_amount == 1))
	{
		mother_close_pipes_all(data);
		ft_wait_part(data);
	}
	free_exec_data(data, exec, data->cmd_amount);
	free(exec);
}
