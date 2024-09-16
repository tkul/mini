/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_red_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 11:50:33 by tkul              #+#    #+#             */
/*   Updated: 2024/09/05 18:12:10 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_for_in_file(t_data *data, t_exec *exec)
{
	(void)data;
	if (!access(exec->in_file, F_OK) && access(exec->in_file, R_OK) == -1)
	{
		exec->should_run = 1;
		if (!exec->is_here_doc)
			ft_set_exec_err(data, exec, ERR_PERMISSION_DENIED, exec->in_file);
		return (126);
	}
	exec->should_run = 1;
	if (exec->is_here_doc)
		return (0);
	ft_set_exec_err(data, exec, ERR_NO_FILE_OR_DIR, exec->in_file);
	return (ERR_NO_FILE_OR_DIR);
}

static int	ft_for_out_file(t_data *data, t_exec *exec)
{
	(void)data;
	if (!access(exec->out_file, F_OK) && access(exec->out_file, W_OK) == -1)
	{
		exec->should_run = 1;
		ft_set_exec_err(data, exec, ERR_PERMISSION_DENIED, exec->out_file);
		return (1);
	}
	exec->should_run = 1;
	ft_set_exec_err(data, exec, ERR_NO_FILE_OR_DIR, exec->out_file);
	return (ERR_NO_FILE_OR_DIR);
}

int	ft_open_check_files(t_exec *exec, int status, t_data *data)
{
	if (exec->in_file || exec->is_here_doc)
	{
		if (exec->in_type == IN_RED && exec->should_run == 0)
			exec->in_fd = open(exec->in_file, O_RDONLY);
		if (exec->in_fd == -1 && exec->should_run == 0)
			return (ft_for_in_file(data, exec));
	}
	if (exec->out_file && exec->should_run == 0)
	{
		if (exec->out_type == OUT_RED)
		{
			if (exec->out_file == NULL)
				return (1);
			exec->out_fd = open(exec->out_file, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		}
		else if (exec->out_type == APP_RED)
			exec->out_fd = open(exec->out_file, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		if (exec->out_fd == -1 && exec->should_run == 0)
			return (ft_for_out_file(data, exec));
	}
	return (status);
}

int	ft_is_redirection_single(t_token *token)
{
	if (token->type == IN_RED || token->type == OUT_RED
		|| token->type == APP_RED || token->type == HER_DOC)
		return (1);
	return (0);
}
