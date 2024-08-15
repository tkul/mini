/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thisfilewilldeleted.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:44:54 by tkul              #+#    #+#             */
/*   Updated: 2024/08/15 22:20:45 by tkul             ###   ########.fr       */
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
	t_token	*token;
	int		i;

	token = *data->tokens;
	i = 0;
	while (data->tokens[i])
	{
		if (ft_is_builtins(data->tokens[i]->value) == 1)
		{
			if (ft_strcmp(data->tokens[i]->value, "pwd") == 0)
				ft_pwd(data);
			else if (ft_strcmp(data->tokens[i]->value, "echo") == 0)
				ft_echo(token);
			else if (ft_strcmp(data->tokens[i]->value, "env") == 0)
				ft_env(data);
		}
		i++;
	}
}
