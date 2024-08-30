/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:25:11 by tkul              #+#    #+#             */
/*   Updated: 2024/08/30 18:18:05 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_export_error(t_data *data, char *value)
{
	write(2, "⭐MINISHELL> export: \'", 23);
	write(2, value, strlen(value));
	write(2, "\' not a valid identifier\n", 26);
	data->status = 1;
}

void	ft_process_export_token(t_data *data, t_token *token)
{
	char	*key;
	char	*value;

	if (ft_strchr(token->value, '='))
	{
		key = ft_substr(token->value, 0, ft_strchr(token->value, '=')
				- token->value);
		value = ft_strchr(token->value, '=') + 1;
		ft_setenv(data, key, value);
		ft_update_export_entry(data, key, value);
		free(key);
	}
	else
		ft_update_export_entry(data, token->value, "");
}

void	ft_export(t_data *data, int *index)
{
	t_token	*token;
	int		i;

	i = 0;
	token = data->tokens[*index]->next;
	if (!token)
	{
		while (data->export[i])
			printf("declare -x %s\n", data->export[i++]);
		return ;
	}
	while (token)
	{
		if (!(my_isalpha(token->value)))
		{
			ft_handle_export_error(data, token->value);
			token = token->next;
			break ;
		}
		ft_process_export_token(data, token);
		token = token->next;
	}
}
