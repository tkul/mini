/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 22:49:55 by tkul              #+#    #+#             */
/*   Updated: 2024/08/29 04:05:39 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_entry(char **array, char *key)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (strncmp(array[i], key, strlen(key)) == 0)
		{
			free(array[i]);
			while (array[i + 1])
			{
				array[i] = array[i + 1];
				i++;
			}
			array[i] = NULL;
			return ;
		}
		i++;
	}
}

void	ft_unset_unsetter(t_data *data, char *key)
{
	remove_entry(data->env, key);
	remove_entry(data->export, key);
}

int	ft_unset(t_data *data, int *index)
{
	t_token	*token;

	token = data->tokens[*index]->next;
	while (token)
	{
		if (ft_strchr(token->value, '=') || !(my_isalpha(token->value)))
		{
			write(2, "⭐MINISHELL> unset: \'", 22);
			write(2, token->value, strlen(token->value));
			write(2, "\' not a valid identifier\n", 26);
			data->status = 1;
			token = token->next;
			break ;
		}
		ft_unset_unsetter(data, token->value);
		token = token->next;
	}
	return (SUCCESS);
}

