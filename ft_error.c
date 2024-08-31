/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:14:09 by tkul              #+#    #+#             */
/*   Updated: 2024/08/31 03:47:44 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_data *data, int error)
{
	if (error == SYNTAX_ERROR)
	{
		data->status = SYNTAX_ERROR;
		printf("Error: syntax error near unexpected token\n");
	}
	if (error == EXIT_ERROR)
	{
		data->status = EXIT_ERROR;
		printf("exit: numeric argument required\n");
	}
}


void	ft_set_exec_err(t_data *data, t_exec *exec, int err, char *value)
{
	(void)data;
	if (exec->err_no)
		return ;
	exec->err_no = err;
	exec->err_value = value;
}

void	ft_exec_error(int err, char *value, int status)
{
	if (err == ERR_NO_FILE_OR_DIR)
	{
		printf("minishell: %s: No such file or directory\n", value);
		status = 127;
	}
	if (err == ERR_PERMISSION_DENIED)
	{
		printf("minishell: %s: Permission denied\n", value);
		status = 126;
	}
	if (err == ERR_IS_DIR)
	{
		printf("minishell: %s: is a directory\n", value);
		status = 126;
	}
}

void	ft_print_exec_errors(t_data *data, t_exec **exec)
{
	int	i;

	i = 0;
	while (i < data->cmd_amount)
	{
		if (exec[i]->err_no)
			ft_exec_error(exec[i]->err_no, exec[i]->err_value, 0);
		i++;
	}
}