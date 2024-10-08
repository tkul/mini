/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 23:53:32 by tkul              #+#    #+#             */
/*   Updated: 2024/09/02 15:52:30 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_exit_value(const char *value)
{
	int	i;

	i = 0;
	if (value[i] == '-' || value[i] == '+')
		i++;
	while (value[i])
	{
		if (!ft_isdigit(value[i]))
			return (EXIT_ERROR);
		i++;
	}
	return (0);
}

void	process_exit_code(const char *value, int *exit_code)
{
	*exit_code = ft_atoi(value);
	if (*exit_code < 0)
		*exit_code = 256 + (*exit_code % 256);
}

int	ft_check_arg(t_data *data, int *exit_code, t_token *token)
{
	if (token && token->next && token->next->next)
	{
		write(2, "⭐MINISHELL> : too many arguments\n", 35);
		*exit_code = 1;
		data->status = *exit_code;
		return (1);
	}
	return (0);
}

void	ft_exit(t_data *data, int *index)
{
	t_token	*token;
	int		exit_code;
	int		validation_code;

	exit_code = 0;
	token = data->tokens[*index];
	printf("exit\n");
	if (ft_check_arg(data, &exit_code, token))
		return ;
	else if (token && token->next)
	{
		validation_code = validate_exit_value(token->next->value);
		if (validation_code != 0)
		{
			ft_error(data, EXIT_ERROR);
			exit_code = validation_code;
		}
		else
			process_exit_code(token->next->value, &exit_code);
	}
	data->status = exit_code;
	exit(exit_code);
}
