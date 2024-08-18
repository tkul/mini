/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 23:52:47 by tkul              #+#    #+#             */
/*   Updated: 2024/08/17 23:53:18 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	n_control(char *str)
{
	int	i;

	i = 2;
	if (str[0] != '-' || str[1] != 'n')
		return (ERROR);
	while (str[i])
	{
		if (str[i] != 'n')
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

void	ft_echo(t_data *data, int index)
{
	t_token	*token;
	int		n_flag;
	int		control;

	n_flag = 1;
	token = data->tokens[index];
	control = 0;
	if (!token->next)
	{
		printf("\n");
		return ;
	}
	token = token->next;
	while (token)
	{
		if (n_flag == 1 && n_control(token->value) == SUCCESS)
		{
			token = token->next;
			control = 1;
			continue ;
		}
		else
			n_flag = 0;
		if (token->type == ARG)
		{
			printf("%s", token->value);
			if (token->next)
				printf(" ");
		}
		token = token->next;
	}
	if (!control)
		printf("\n");
}
