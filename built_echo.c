/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 23:52:47 by tkul              #+#    #+#             */
/*   Updated: 2024/08/21 10:41:43 by tkul             ###   ########.fr       */
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

int	ft_echo_handle_n_flag(t_token *token, int n_flag)
{
	if (n_flag && n_control(token->value) == SUCCESS)
		return (1);
	return (0);
}

void	ft_echo_print_tokens(t_token *token)
{
	int	control;
	int	n_flag;

	n_flag = 1;
	control = 0;
	while (token)
	{
		if (n_flag && ft_echo_handle_n_flag(token, n_flag))
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

void	ft_echo(t_data *data, int *index)
{
	t_token	*token;

	token = data->tokens[*index];
	if (!token->next)
	{
		printf("\n");
		return ;
	}
	token = token->next;
	ft_echo_print_tokens(token);
}
