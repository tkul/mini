/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 23:46:21 by tkul              #+#    #+#             */
/*   Updated: 2024/09/05 13:41:49 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_find_helper(t_token *tmp, t_exec **exec, int i, t_token *token)
{
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			if (!exec[i]->type)
				exec[i]->type = ft_find_exec_type(exec, token, i);
		}
		tmp = tmp->next;
	}
}

void	ft_start_exec(t_data *data, t_exec **exec, t_token *token, int i)
{
	int		err;
	t_token	*tmp;

	err = 0;
	tmp = token;
	g_qsignal = 1;
	ft_init_here_docs(data, exec, i, token);
	ft_find_helper(tmp, exec, i, token);
	err = ft_exec_init_redirection(data, exec[i], token);
	if (err)
	{
		ft_set_exec_err(data, exec[i], err, token->value);
		return (ft_print_exec_error(data, exec[i]));
	}
	if (data->cmd_amount > 1)
	{
		if (token->type == CMD || exec[i]->type == CMD_WITHOUT_CMD)
			ft_exec_part(data, exec[data->index], token);
	}
	else
		ft_run_single_cmd(data, exec, i, token);
	g_qsignal = 0;
}

static void	ft_execute(t_data *data, t_exec **exec)
{
	int		i;
	t_token	*token;

	i = 0;
	while (data->tokens[i])
	{
		data->index = i;
		token = data->tokens[i];
		data->check = ft_is_builtins(token->value);
		ft_start_exec(data, exec, token, data->index);
		i++;
	}
	if (!(data->check > 0 && data->cmd_amount == 1))
	{
		mother_close_pipes_all(data);
		ft_wait_part(data);
	}
	free_exec_data(data, exec, data->cmd_amount);
	free(exec);
}

void	ft_start_execute(t_data *data)
{
	int		i;
	t_exec	**exec;

	i = 0;
	data->index = 0;
	data->cmd_amount = ft_count_cmds(data, data->tokens);
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
	ft_execute(data, exec);
}
