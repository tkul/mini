/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thisfilewilldeleted.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tugcekul <tugcekul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:44:54 by tkul              #+#    #+#             */
/*   Updated: 2024/08/18 02:37:29 by tugcekul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_tokens(t_token **token)
{
	t_token	**tmp;
	t_token	*next;
	int		i;

	if (!token || !*token)
		return ;
	tmp = token;
	i = 0;
	while (tmp[i])
	{
		next = tmp[i];
		while (next)
		{
			printf("Token %d: type:%d, %s$\n", i, next->type, next->value);
			next = next->next;
		}
		i++;
	}
}

void	ft_execute(t_data *data)
{
	int	i;

	i = 0;
	while (data->tokens[i])
	{
		if (ft_is_builtins(data->tokens[i]->value) == 1)
		{
			if (ft_strcmp(data->tokens[i]->value, "pwd") == 0)
				ft_pwd(data);
			else if (ft_strcmp(data->tokens[i]->value, "echo") == 0)
				ft_echo(data, i);
			else if (ft_strcmp(data->tokens[i]->value, "env") == 0)
				ft_env(data);
			else if (ft_strcmp(data->tokens[i]->value, "exit") == 0)
				ft_exit(data, i);
			else if (ft_strcmp(data->tokens[i]->value, "cd") == 0)
				ft_cd(data, i);
			else if (ft_strcmp(data->tokens[i]->value, "export") == 0)
				ft_export(data, i);
			else if (ft_strcmp(data->tokens[i]->value, "unset") == 0)
				ft_unset(data, i);
		}
		i++;
	}
}
