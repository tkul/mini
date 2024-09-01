/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 11:19:44 by tkul              #+#    #+#             */
/*   Updated: 2024/09/01 14:52:20 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes_all(int *pipes, int cmd_amount, int i)
{
	int	j;

	j = -1;
	while (++j < cmd_amount * 2)
	{
		if ((i == 0 && j != i * 2 + 1) || (i == cmd_amount - 1 && j != (i - 1)
				* 2) || (i != 0 && i != cmd_amount - 1 && j != (i - 1) * 2
				&& j != i * 2 + 1))
		{
			close(pipes[j]);
		}
	}
}

void	mother_close_pipes_all(t_data *data)
{
	int j;

	j = 0;
	while (j < data->cmd_amount * 2)
	{
		close(data->pipes[j]);
		j++;
	}
}