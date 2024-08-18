/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 23:53:32 by tkul              #+#    #+#             */
/*   Updated: 2024/08/17 23:55:44 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_exit_value(const char *value)
{
	int	i;

	i = 0;
	if (value[i] == '-')
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

void	ft_exit(t_data *data, int index)
{
	t_token	*token;
	int		exit_code;
	int		validation_code;

	exit_code = 0;
	token = data->tokens[index];
	printf("exit\n");
	if (token && token->next && token->next->next)
	{
		write(2, "exit: too many arguments\n", 26);
		exit_code = 1;
	}
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
// void	ft_exit(t_data *data)
// {
// 	t_token *token;
// 	int exit_code;
// 	int i;

// 	i = 0;
// 	exit_code = 0;
// 	token = *data->tokens;
// 	printf("exit\n");
// 	if (token && token->next && token->next->next)
// 	{
// 		write(2, "exit: too many arguments\n", 26);
// 		exit_code = 1;
// 	}
// 	else if (token && token->next)
// 	{
// 		while (token->next->value[i])
// 		{
// 			if (i == 0 && token->next->value[i] == '-')
// 			{
// 				i++;
// 				continue ;
// 			}
// 			if (!ft_isdigit(token->next->value[i]))
// 			{
// 				ft_error(data, EXIT_ERROR);
// 				exit_code = 255;
// 				break ;
// 			}
// 			i++;
// 		}
// 		if (exit_code == 0)
// 			exit_code = ft_atoi(token->next->value);
// 	}
// 	data->status = exit_code;
// 	exit(exit_code);
// }