/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:28:43 by tkul              #+#    #+#             */
/*   Updated: 2024/09/03 12:18:20 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_part(t_data *data, t_exec *exec, t_token *token)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		ft_run_pipes(data, exec, data->index, token);
	data->forks[data->index] = pid;
}

void	ft_wait_part(t_data *data)
{
	int	i;

	i = data->cmd_amount - 1;
	while (i >= 0)
	{
		if (i == data->cmd_amount - 1)
		{
			waitpid(data->forks[i], &data->status, 0);
			if (WIFEXITED(data->status))
				data->status = WEXITSTATUS(data->status);
		}
		waitpid(data->forks[i], NULL, 0);
		i--;
	}
}
