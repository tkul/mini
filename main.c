/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tugcekul <tugcekul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:35:45 by tkul              #+#    #+#             */
/*   Updated: 2024/08/05 00:59:06 by tugcekul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_getenv_by_key(char *key, char **env)
{
	int i;
	int j;
	int k;
	char *result;

	i = 0;
	while (env[i])
	{
		j = 0;
		k = 0;
		while (env[i][j] && key[k] && env[i][j] == key[k])
		{
			j++;
			k++;
		}
		if (key[k] == '\0' && env[i][j] == '=')
		{
			result = ft_strdup(env[i] + j + 1);
			return (result);
		}
		i++;
	}
	return (NULL);
}

char **ft_getenv(char **env)
{
	int i;
	char **result;

	i = 0;
	while (env[i])
		i++;
	result = malloc(sizeof(char *) * (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (env[i])
	{
		result[i] = ft_strdup(env[i]);
		i++;
	}
	result[i] = NULL;
	return (result);
}
int ft_init_data(t_data *data, char **env)
{
	data->cmd = NULL;
	data->status = 0;
	data->is_pipe = 0;
	data->env = ft_getenv(env);
	data->tokens = NULL;
	data->cwd = getcwd(NULL, 0);
	data->exit_status = NULL;
	data->cmd_count = 0;
	data->pipe_count = 0;
	return (0);
}

int main(int ac, char **av, char **env)
{
	t_data *data;
	int exit_status;
	
	if (ac != 1 || !av)
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	ft_signals();
	if (ft_init_data(data, env))
		return (free(data), 0);
	ft_start_shell(data);
	exit_status = data->status;
	free(data);
	return (exit_status);
}