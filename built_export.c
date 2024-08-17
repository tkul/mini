/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:25:11 by tkul              #+#    #+#             */
/*   Updated: 2024/08/18 01:29:05 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_realloc(char **env, int size)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	new[i] = NULL;
	free(env);
	return (new);
}

void	ft_set_export(t_data *data, char *key, char *value)
{
	int		i;
	char	*new;
	char	*tmp;

	i = 0;
	printf("key:%s\n", key);
	printf("value:%s\n", value);
	while (data->export[i])
	{
		printf("export:%s\n", data->export[i]);
		if (ft_strncmp(data->export[i], key, ft_strlen(key)) == 0)
		{
			free(data->export[i]);
			tmp = ft_strjoin(key, "=");
			new = ft_strjoin(tmp, value);
			free(tmp);
			data->export[i] = new;
			return ;
		}
		i++;
	}
	data->export = ft_realloc(data->export, i + 1);
	if (value && *value)
	{
		tmp = ft_strjoin(key, "=");
		new = ft_strjoin(tmp, value);
	}
	else
	{
		tmp = ft_strdup(key);
		new = ft_strjoin(tmp, value);
	}
	free(tmp);
	data->export[i] = new;
	data->export[i + 1] = NULL;
}

void	ft_export(t_data *data, int index)
{
	t_token	*token;
	char	*key;
	char	*value;
	int		i;

	token = data->tokens[index];
	i = 0;
	if (!token->next)
	{
		while (data->export[i])
			printf("declare -x %s\n", data->export[i++]);
		return ;
	}
	token = token->next;
	while (token)
	{
		if (ft_strchr(token->value, '='))
		{
			key = ft_substr(token->value, 0, ft_strchr(token->value, '=')
					- token->value);
			value = ft_strchr(token->value, '=') + 1;
			ft_setenv(data, key, value);
			ft_set_export(data, key, value);
			free(key);
		}
		else
			ft_set_export(data, token->value, "");
		token = token->next;
	}
}
