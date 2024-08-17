/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 23:54:12 by tkul              #+#    #+#             */
/*   Updated: 2024/08/18 00:44:16 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setenv(t_data *data, char *key, char *value)
{
	int		i;
	char	*new;
	char	*tmp;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], key, ft_strlen(key)) == 0)
		{
			free(data->env[i]);
			tmp = ft_strjoin(key, "=");
			new = ft_strjoin(tmp, value);
			free(tmp);
			data->env[i] = new;
			return ;
		}
		i++;
	}
	data->env = ft_realloc(data->env, i + 1);
	tmp = ft_strjoin(key, "=");
	new = ft_strjoin(tmp, value);
	free(tmp);
	data->env[i] = new;
	data->env[i + 1] = NULL;
}

void	ft_cd(t_data *data, int index)
{
	struct stat	buf;
	t_token		*token;

	data->old_pwd = getcwd(NULL, 0);
	token = data->tokens[index];
	if (!token->next)
	{
		data->path = ft_getenv_by_key("HOME", data->env);
		if (!data->path)
		{
			write(2, "cd: HOME not set\n", 17);
			data->status = ERROR;
			return ;
		}
	}
	else
		data->path = token->next->value;
	data->ret = stat(data->path, &buf);
	if (data->ret == -1)
	{
		write(2, "cd: no such file or directory: ", 31);
		write(2, data->path, ft_strlen(data->path));
		write(2, "\n", 1);
		data->status = ERROR;
		return ;
	}
	if (!S_ISDIR(buf.st_mode))
	{
		write(2, "cd: not a directory: ", 21);
		write(2, data->path, ft_strlen(data->path));
		write(2, "\n", 1);
		data->status = ERROR;
		return ;
	}
	if (chdir(data->path) == -1)
	{
		write(2, "cd: error\n", 10);
		data->status = ERROR;
		return ;
	}
	ft_setenv(data, "OLDPWD", data->old_pwd);
	data->cwd = getcwd(NULL, 0);
	data->status = SUCCESS;
}
