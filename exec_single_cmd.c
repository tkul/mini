/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 11:28:53 by tkul              #+#    #+#             */
/*   Updated: 2024/09/05 12:35:51 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(t_data *data, t_exec **exec, int i)
{
	t_token	*token;

	token = data->tokens[i];
	(void)exec;
	ft_set_path(data, token, exec[i]);
	ft_print_exec_error(data, exec[i]);
	if (data->path == NULL)
		return ;
	ft_set_args(data, token);
	data->forks[0] = fork();
	if (!data->forks[0])
	{
		if (exec[i]->is_without_cmd)
			mother_close_pipes_all(data);
		ft_dup_redictions(exec[i], data);
		execve(data->path, data->args, data->env);
		exit(data->status);
	}
}

void	ft_run_single_cmd(t_data *data, t_exec **exec, int i, t_token *token)
{
	int	fd1;
	int	fd2;

	if (data->check > 0)
	{
		fd1 = dup(1);
		fd2 = dup(0);
		ft_run_builtin(data, i, token, exec[i]);
		return (close_redir_fd(data, exec[0], fd1, fd2));
	}
	else
		ft_execve(data, exec, i);
	return ;
}
