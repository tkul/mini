/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:36:49 by tkul              #+#    #+#             */
/*   Updated: 2024/09/02 18:37:07 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_data *data, int error)
{
	if (error == SYNTAX_ERROR)
	{
		data->status = SYNTAX_ERROR;
		write(2, "Error: syntax error near unexpected token\n", 42);
	}
	if (error == EXIT_ERROR)
	{
		data->status = EXIT_ERROR;
		write(2, "exit: numeric argument required\n", 33);
	}
}
