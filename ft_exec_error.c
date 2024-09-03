/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:14:09 by tkul              #+#    #+#             */
/*   Updated: 2024/09/03 12:06:39 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_exec_err(t_data *data, t_exec *exec, int err, char *value)
{
	(void)data;
	if (exec->err_no)
		return ;
	exec->err_no = err;
	exec->err_value = value;
	exec->should_run = 1;
}

void	ft_err_output(char *value, int err)
{
	write(2, "minishell: ", 11);
	write(2, value, ft_strlen(value));
	write(2, ": ", 2);
	write(2, strerror(err), ft_strlen(strerror(err)));
	write(2, "\n", 1);
}

void	ft_error_cases(t_data *data, t_exec *exec, int err, char *value)
{
	if (err == ERR_NO_FILE_OR_DIR)
	{
		data->status = 1;
		exec->should_run = 1;
		ft_err_output(value, ENOENT);
	}
	if (err == ERR_PERMISSION_DENIED)
	{
		data->status = 1;
		exec->should_run = 1;
		ft_err_output(value, EACCES);
	}
	if (err == ERR_PERMISSION_DENIED2)
	{
		data->status = 126;
		exec->should_run = 1;
		ft_err_output(value, EACCES);
	}
}

void	ft_exec_error(t_data *data, t_exec *exec, int err, char *value)
{
	if (err == ERR_NO_SUCH_FILE)
	{
		data->status = 127;
		exec->should_run = 1;
		ft_err_output(value, ENOENT);
	}
	else if (err == CMD_NOT_FOUND)
	{
		data->status = 127;
		exec->should_run = 1;
		write(2, "minishell: ", 11);
		write(2, value, ft_strlen(value));
		write(2, ": command not found\n", 20);
	}
	if (err == ERR_IS_DIR)
	{
		data->status = 126;
		exec->should_run = 1;
		ft_err_output(value, EISDIR);
	}
	ft_error_cases(data, exec, err, value);
}

void	ft_print_exec_errors(t_data *data, t_exec **exec)
{
	int	i;

	i = 0;
	while (i < data->cmd_amount)
	{
		if (exec[i]->err_no)
			ft_exec_error(data, exec[i], exec[i]->err_no, exec[i]->err_value);
		i++;
	}
}

void ft_print_exec_error(t_data *data, t_exec *exec)
{
	if (exec->err_no)
		ft_exec_error(data, exec, exec->err_no, exec->err_value);
}

