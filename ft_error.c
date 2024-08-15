/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:14:09 by tkul              #+#    #+#             */
/*   Updated: 2024/08/14 11:03:27 by tkul             ###   ########.fr       */
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
}
