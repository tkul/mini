/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 23:55:15 by tkul              #+#    #+#             */
/*   Updated: 2024/09/02 15:58:03 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_data *data)
{
	printf("%s\n", data->cwd);
	data->status = SUCCESS;
}

void	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
	data->status = SUCCESS;
}
