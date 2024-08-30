/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:14:09 by tkul              #+#    #+#             */
/*   Updated: 2024/08/30 22:41:48 by tkul             ###   ########.fr       */
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
	// ft_print_exec_errors(data, exec);
}

// void	ft_print_exec_errors(t_data *data, t_exec *exec)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->cmd_amount)
// 	{
// 		if (exec->err_no)
// 		{
// 			if (exec->err_no == ERR_NO_FILE_OR_DIR)
// 			{
// 				data->status = ERR_NO_FILE_OR_DIR;
// 				printf("minishell: %s: No such file or directory\n", exec->err_value);
// 			}
// 			if (exec->err_no == ERR_PERMISSION_DENIED)
// 			{
// 				data->status = 1;
// 				printf("minishell: %s: Permission denied\n", exec->err_value);
// 			}
// 			if (exec->err_no == ERR_IS_DIR)
// 			{
// 				data->status = 126;
// 				printf("minishell: %s: is a directory\n", exec->err_value);
// 			}

// 		}
// 		i++;
// 	}
// }