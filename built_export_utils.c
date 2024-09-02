/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:53:14 by tkul              #+#    #+#             */
/*   Updated: 2024/09/02 15:57:07 by tkul             ###   ########.fr       */
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
	ft_free_array(env);
	return (new);
}

char	*ft_create_export_entry(const char *key, const char *value)
{
	char	*tmp;
	char	*entry;

	if (value && *value)
	{
		tmp = ft_strjoin(key, "=");
		entry = ft_strjoin(tmp, value);
		free(tmp);
	}
	else
	{
		tmp = ft_strdup(key);
		entry = ft_strjoin(tmp, "");
		free(tmp);
	}
	return (entry);
}

void	ft_update_export_entry(t_data *data, char *key, char *value)
{
	char	*new_entry;
	int		i;

	i = 0;
	while (data->export[i])
	{
		if (ft_strncmp(data->export[i], key, ft_strlen(key)) == 0)
		{
			free(data->export[i]);
			new_entry = ft_create_export_entry(key, value);
			data->export[i] = new_entry;
			return ;
		}
		i++;
	}
	data->export = ft_realloc(data->export, i + 1);
	new_entry = ft_create_export_entry(key, value);
	data->export[i] = new_entry;
	data->export[i + 1] = NULL;
}
