/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 11:15:02 by tkul              #+#    #+#             */
/*   Updated: 2024/09/03 23:03:08 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_absolute_path(t_data *data, t_token *token, t_exec *exec,
		char *path)
{
	struct stat	buf;

	stat(token->value, &buf);
	if (errno == EACCES)
		return (ft_set_exec_err(data, exec, ERR_PERMISSION_DENIED,
				token->value), 1);
	if (S_ISDIR(buf.st_mode))
		return (ft_set_exec_err(data, exec, ERR_IS_DIR, token->value), 126);
	if (access(path, F_OK) == -1)
		return (ft_set_exec_err(data, exec, ERR_NO_SUCH_FILE, token->value),
			127);
	if (access(path, X_OK) == -1)
		return (ft_set_exec_err(data, exec, ERR_PERMISSION_DENIED2,
				token->value), 126);
	return (0);
}

char	*ft_get_command_path(t_data *data, t_token *token)
{
	char	*path;
	char	*tmp2;

	tmp2 = ft_getenv_by_key("PATH", data->env);
	path = find_in_path(tmp2, token->value);
	free(tmp2);
	return (path);
}

int	ft_absolute_path(t_data *data, t_token *token, t_exec *exec, char *path)
{
	int	status;

	status = ft_find_absolute_path(data, token, exec, path);
	if (status)
		data->status = status;
	return (status);
}

void	ft_relative_path(t_data *data, t_exec *exec, t_token *token)
{
	ft_set_exec_err(data, exec, CMD_NOT_FOUND, token->value);
	data->status = 127;
}

void	ft_set_path(t_data *data, t_token *token, t_exec *exec)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			if (data->t_path)
				free(data->t_path);
			data->t_path = ft_get_command_path(data, tmp);
			if (ft_strchr(tmp->value, '/'))
			{
				data->status = ft_absolute_path(data, tmp, exec, data->t_path);
				if (data->t_status)
					break ;
			}
			else if (!data->t_path)
			{
				ft_relative_path(data, exec, tmp);
				break ;
			}
		}
		tmp = tmp->next;
	}
	data->path = data->t_path;
}
