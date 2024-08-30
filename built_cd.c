/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 23:54:12 by tkul              #+#    #+#             */
/*   Updated: 2024/08/30 20:27:05 by tkul             ###   ########.fr       */
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

void	ft_print_error(const char *path, const char *msg)
{
	write(2, "⭐MINISHELL> ", 14);
	write(2, msg, ft_strlen(msg));
	if (path)
	{
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
	}
}

int	ft_check_directory(t_data *data)
{
	struct stat	buf;

	data->ret = stat(data->path, &buf);
	if (data->ret == -1)
	{
		ft_print_error(data->path, "cd: no such file or directory: ");
		data->status = ERROR;
		return (0);
	}
	if (!S_ISDIR(buf.st_mode))
	{
		ft_print_error(data->path, "cd: not a directory: ");
		data->status = ERROR;
		return (0);
	}
	return (1);
}

void	ft_cd_change_directory(t_data *data)
{
	if (chdir(data->path) == -1)
	{
		write(2, "cd: error\n", 10);
		data->status = ERROR;
		return ;
	}
	ft_setenv(data, "OLDPWD", data->old_pwd);
	data->cwd = getcwd(NULL, 0);
	ft_setenv(data, "PWD", data->cwd);
	ft_update_or_add_export_entry(data, "PWD", data->cwd);
	data->status = SUCCESS;
}

void	ft_cd(t_data *data, int *index)
{
	t_token	*token;

	data->old_pwd = getcwd(NULL, 0);
	token = data->tokens[*index];
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
	if (!ft_check_directory(data))
		return ;
	ft_cd_change_directory(data);
}
