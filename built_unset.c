/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 22:49:55 by tkul              #+#    #+#             */
/*   Updated: 2024/08/21 14:37:10 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//unset tekrar konrol et, tam doğru çalışmıyor

void	ft_unset_unsetter(t_data *data, char *key)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (strncmp(data->env[i], key, strlen(key)) == 0
			&& data->env[i][strlen(key)] == '=')
		{
			free(data->env[i]);
			while (data->env[i + 1])
			{
				data->env[i] = data->env[i + 1];
				i++;
			}
			data->env[i] = NULL;
			break ;
		}
		i++;
	}
	i = 0;
	while (data->export[i])
	{
		if (strncmp(data->export[i], key, strlen(key)) == 0
			&& data->export[i][strlen(key)] == '=')
		{
			free(data->export[i]);
			while (data->export[i + 1])
			{
				data->export[i] = data->export[i + 1];
				i++;
			}
			data->export[i] = NULL;
			break ;
		}
		i++;
	}
}

int	ft_exp_uns_is_valid(t_data *data, char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]) || !ft_isalpha(str[0]))
	{
		ft_error(data, ERR_NOT_VALID_IDFR);
		return (1);
	}
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_error(data, ERR_NOT_VALID_IDFR);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_unset(t_data *data, int *index)
{
	t_token	*token;
	int		flag;
	int		ret;
	int		i;

	i = 0;
	flag = 0;
	if (index < 0 || !data->tokens || !data->tokens[*index])
		return (ERROR);
	token = data->tokens[*index];
	while (token)
	{
		if (strchr(token->value, '=') || !(my_isalpha(token->value[i])))
		{
			write(2, "⭐MINISHELL> ", 14);
			write(2, "unset: \'", 9);
			write(2, token->value, strlen(token->value));
			write(2, "\' not a valid identifier\n", 26);
			flag = 1;
			token = token->next;
			break ;
		}
		ret = ft_exp_uns_is_valid(data, token->value);
		if (ret)
		{
			flag = ret;
			token = token->next;
			continue ;
		}
		ft_unset_unsetter(data, token->value);
		token = token->next;
		i++;
	}
	return (flag);
}
