/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:49:03 by tkul              #+#    #+#             */
/*   Updated: 2024/09/03 13:29:23 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_qsignal = 0;

char	*ft_getenv_by_key(char *key, char **env)
{
	int		i;
	int		j;
	int		k;
	char	*result;

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

char	**ft_getenv(char **env)
{
	int		i;
	char	**result;

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

void	ft_init_data(t_data *data, char **env)
{
	data->cmd = NULL;
	data->status = 0;
	data->env = ft_getenv(env);
	data->export = ft_getenv(env);
	data->tokens = NULL;
	data->cwd = getcwd(NULL, 0);
	data->pipe_count = 0;
	data->token_buffer = NULL;
	data->cmd_amount = 0;
	data->check = 0;
	data->forks = NULL;
	data->pipes = NULL;
	data->path = NULL;
	data->args = NULL;
	data->i = 0;
	data->j = 0;
	data->ret = 0;
	data->old_pwd = NULL;
	data->is_red = 0;
	data->last = NULL;
	data->new_token = NULL;
	data->is_really_env = 0;
	data->t_path = NULL;
	data->t_status = 0;
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	int		exit_status;

	if (ac != 1 || !av)
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	ft_signals();
	ft_init_data(data, env);
	ft_start_shell(data);
	exit_status = data->status;
	free(data);
	return (exit_status);
}
