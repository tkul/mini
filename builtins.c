/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tugcekul <tugcekul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:25:11 by tkul              #+#    #+#             */
/*   Updated: 2024/08/16 02:36:40 by tugcekul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_data *data)
{
	printf("%s\n", data->cwd);
}

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

void	ft_echo(t_token *t)
{
	t_token	*token;
	int		n_flag;
	int		control;

	n_flag = 1;
	token = t;
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

void	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
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




int validate_exit_value(const char *value)
{
    int i = 0;
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

void process_exit_code(const char *value, int *exit_code)
{
    *exit_code = ft_atoi(value);
    if (*exit_code < 0)
        *exit_code = 256 + (*exit_code % 256);
}

void	ft_exit(t_data *data)
{
    t_token *token;
    int exit_code;
	int validation_code;
	
	exit_code = 0;
	token = *data->tokens;
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
