/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:14:09 by tkul              #+#    #+#             */
/*   Updated: 2024/08/29 09:33:11 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_data *data, int error)
{
	if (error == CMD_NOT_FOUND)
	{
		data->status = CMD_NOT_FOUND;
		printf("Error: command not found\n");
	}
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


// void	ft_set_exec_err(t_exec *exec, int err, char *value)
// {
// 	if (exec->err_no)
// 		return ;
// 	exec->err_no = err;
// 	exec->err_value = value;
// }

// void	ft_print_exec_errors(t_data *data, t_exec **exec)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->cmd_amount)
// 	{
// 		if (exec[i]->err_no)
// 			ft_error(exec[i]->err_no, exec[i]->err_value);
// 		i++;
// 	}
// }