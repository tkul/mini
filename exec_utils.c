/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:54:42 by tkul              #+#    #+#             */
/*   Updated: 2024/08/27 15:37:49 by tkul             ###   ########.fr       */
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
	else if (token->type == ARG)
		return (CMD_ARG);
	return (CMD_PATH);
}
void    ft_init_exec(t_data *data, t_exec **exec, t_token *token)
{
    int i;

    i = 0;
    while (i < data->cmd_amount)
    {
        exec[i] = malloc(sizeof(t_exec));
        if (!exec[i])
            return ;
        exec[i]->heredocs = NULL;
        exec[i]->err_no = 0;
        exec[i]->err_value = NULL;
        exec[i]->is_without_cmd = isredwocmd(token, data->cmd_amount, i);
        exec[i]->out_type = 0;
        exec[i]->out_file = NULL;
        exec[i]->in_file = NULL;
		exec[i]->should_run = 0;
        exec[i]->in_type = 0;
		exec[i]->here_doc_idx = 0;
		ft_is_without_cmd(exec[i], data);
        exec[i]->is_here_doc = ft_is_here_doc(token);
        exec[i]->in_fd = 0;
        exec[i]->out_fd = 0;
        exec[i]->count_heredocs = ft_count_heredocs(token);
		exec[i]->type = 0;
        data->exec = exec;
        i++;
    }
}

void	ft_run_builtin(t_data *data, int i)
{ 
	if (ft_strcmp(data->tokens[i]->value, "echo") == 0)
		ft_echo(data, &i);
	else if (ft_strcmp(data->tokens[i]->value, "pwd") == 0)
		ft_pwd(data);
	else if (ft_strcmp(data->tokens[i]->value, "env") == 0)
		ft_env(data);
	else if (ft_strcmp(data->tokens[i]->value, "cd") == 0)
		ft_cd(data, &i);
	else if (ft_strcmp(data->tokens[i]->value, "export") == 0)
		ft_export(data, &i);
	else if (ft_strcmp(data->tokens[i]->value, "unset") == 0)
		ft_unset(data, &i);
	else if (ft_strcmp(data->tokens[i]->value, "exit") == 0)
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

int	ft_is_redirection_single(t_token *token)
{
	if (token->type == IN_RED || token->type == OUT_RED
		|| token->type == APP_RED || token->type == HER_DOC)
		return (1);
	return (0);
}

char	* ft_is_here_doc(t_token *token)
{
	while (token)
	{
		if (token->type == DELIMETER)
			return (token->value);
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
			return (token->value);
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

int	isredwocmd(t_token *tokens, int cmd_amount, int j)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = tokens;
	if (j >= cmd_amount)
		return (0);
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
