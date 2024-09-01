/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:54:42 by tkul              #+#    #+#             */
/*   Updated: 2024/09/01 14:09:01 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_heredocs(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == HER_DOC)
			count++;
		token = token->next;
	}
	return (count);
}

int	ft_find_exec_type(t_exec **exec, t_token *token, int i)
{
	if (exec[i]->is_without_cmd)
		return (CMD_WITHOUT_CMD);
	else if (ft_is_builtins(token->value))
		return (CMD_BUILTIN);
	return (CMD_PATH);
}
void    ft_init_exec(t_data *data, t_exec *exec, t_token *token)
{
	exec->err_no = 0;
	exec->err_value = NULL;
	exec->is_without_cmd = isredwocmd(token);
	exec->out_type = 0;
	exec->out_file = NULL;
	exec->in_file = NULL;
	exec->should_run = 0;
	exec->in_type = 0;
	ft_is_without_cmd(exec, data);
	exec->is_here_doc = ft_is_here_doc(token);
	exec->in_fd = 0;
	exec->out_fd = 0;
	exec->count_heredocs = ft_count_heredocs(token);
	exec->type = 0;
}

void	ft_run_builtin(t_data *data, int i, t_token *token, t_exec *exec)
{
	if (data->cmd_amount == 1 && ft_dup_redictions(exec, data))
		return ;
	if (ft_strcmp(token->value, "echo") == 0)
		ft_echo(data, &i);
	else if (ft_strcmp(token->value, "pwd") == 0)
		ft_pwd(data);
	else if (ft_strcmp(token->value, "env") == 0)
		ft_env(data);
	else if (ft_strcmp(token->value, "cd") == 0)
		ft_cd(data, &i);
	else if (ft_strcmp(token->value, "export") == 0)
		ft_export(data, &i);
	else if (ft_strcmp(token->value, "unset") == 0)
		ft_unset(data, &i);
	else if (ft_strcmp(token->value, "exit") == 0)
		ft_exit(data, &i);
}

int	ft_is_redirection(t_token *token)
{
	while (token)
	{
		if (token->type == IN_RED || token->type == OUT_RED
			|| token->type == APP_RED || token->type == HER_DOC)
			return (1);
		token = token->next;
	}
	return (0);
}

char	* ft_is_here_doc(t_token *token)
{
	while (token)
	{
		if (token->type == DELIMETER)
			return (ft_strdup(token->value));
		token = token->next;
	}
	return (NULL);
}

char	* ft_is_here_doc2(t_exec *exec,t_token *token)
{
	while (token)
	{
		if (!(ft_strcmp(token->value, exec->is_here_doc)))
			token = token->next;
		while (token->type == DELIMETER)
			return (ft_strdup(token->value));
		token = token->next;
	}
	return (NULL);
}

int	isredwocmd_helper(t_token *tokens, int i, t_token *tmp)
{
	if (i == 0)
	{
		tmp = tokens;
		while (tmp)
		{
			if (ft_is_redirection(tmp))
				return (1);
			tmp = tmp->next;
		}
	}
	return (0);
}

int	isredwocmd(t_token *tokens)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == CMD)
			i++;
		if (i != 0)
			return (0);
		tmp = tmp->next;
	}
	return (isredwocmd_helper(tokens, i, tmp));
}

void	ft_is_without_cmd(t_exec *exec, t_data *data)
{
	if (exec->is_without_cmd)
	{
		exec->type = CMD_WITHOUT_CMD;
		data->path = "is_without_cmd";
		data->control = 0;
	}
}
