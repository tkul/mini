/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:18:43 by tkul              #+#    #+#             */
/*   Updated: 2024/08/28 20:33:04 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_pipes(t_data *data)
{
	int	i;

	i = 0;
	data->pipes = malloc(sizeof(int) * (data->cmd_amount * 2));
	data->forks = malloc(sizeof(int) * (data->cmd_amount));
	if (!data->pipes || !data->forks)
	{
		data->status = 1;
		return ;
	}
	while (i < data->cmd_amount)
	{
		if (pipe(data->pipes + i * 2) < 0)
		{
			data->status = ERR_PIPE_INIT;
			return ;
		}
		i++;
	}
}