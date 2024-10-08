/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:37:42 by tkul              #+#    #+#             */
/*   Updated: 2024/09/05 18:42:19 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_run_redirects(t_data *data, t_token *token, t_exec *exec, int i)
{
	if (exec->should_run && !exec->is_here_doc)
		ft_run_commands(data, token, i, exec);
	ft_dup_redictions(exec, data);
	ft_init_dupes(data, exec, i);
	if (data->check > 0)
	{
		ft_run_builtin(data, i, token, exec);
		exit(data->status);
	}
	close_redir_pipe_fd(data, exec, i);
	if (exec->should_run && exec->is_here_doc)
		ft_error(data, ERR_NO_FILE_OR_DIR);
	ft_set_path(data, token, exec);
	if (data->path == NULL)
		exit(data->status);
	ft_set_args(data, token);
	execve(data->path, data->args, data->env);
}

int	ft_exec_init_redirection(t_data *data, t_exec *exec, t_token *token)
{
	data->red_i = 0;
	while (token)
	{
		if (ft_is_redirection_single(token) && token->next)
		{
			if (token->type == IN_RED)
			{
				exec->in_type = token->type;
				if (exec->in_file)
					free(exec->in_file);
				exec->in_file = ft_strdup(token->next->value);
			}
			else if (token->type == OUT_RED || token->type == APP_RED)
			{
				exec->out_type = token->type;
				if (exec->out_file)
					free(exec->out_file);
				if (token->next->value[0] == 1)
					return (ERR_NO_FILE_OR_DIR);
				exec->out_file = ft_strdup(token->next->value);
			}
			data->red_i = ft_open_check_files(exec, data->red_i, data);
		}
		token = token->next;
	}
	return (data->red_i);
}
