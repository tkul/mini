/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:25:11 by tkul              #+#    #+#             */
/*   Updated: 2024/08/13 18:21:04 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data)
{
	printf("%s\n", data->cwd);
	return (SUCCESS);
}

int	n_control(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i])
		{
			if (str[i] != 'n')
				return (ERROR);
			i++;
		}
	}
	return (SUCCESS);
}

int	ft_echo(t_data *data)
{
	t_token	*token;

	token = data->tokens[0]; // şimdilik execve olmadığı için ilk tokenı alıyoruz
	while (token)
	{
		if (token->type == ARG)
			printf("%s ", token->value);
		token = token->next;
	}
	printf("\n");
	return (SUCCESS);
}

int	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
	return (SUCCESS);
}
