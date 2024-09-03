/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 11:15:02 by tkul              #+#    #+#             */
/*   Updated: 2024/09/03 03:58:22 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_in_path(char *path, char *cmd)
{
	char	**dirs;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = -1;
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	while (dirs[++i])
	{
		tmp2 = ft_strjoin(dirs[i], "/");
		tmp = ft_strjoin(tmp2, cmd);
		free(tmp2);
		if (access(tmp, F_OK) == 0)
		{
			ft_free_array(dirs);
			return (tmp);
		}
		free(tmp);
	}
	ft_free_array(dirs);
	return (NULL);
}

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

void	ft_set_path(t_data *data, t_token *token, t_exec *exec)
{
	t_token	*tmp;
	int		status;
	char	*path;
	char	*tmp2;

	tmp = token;
	path = NULL;
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			if (path)
				free(path);
			tmp2 = ft_getenv_by_key("PATH", data->env);
			path = find_in_path(tmp2, tmp->value);
			free(tmp2);
			if (ft_strchr(tmp->value, '/'))
			{
				status = ft_find_absolute_path(data, tmp, exec, path);
				if (status)
				{
					data->status = status;
					break ;
				}
			}
			else if (!path)
			{
				ft_set_exec_err(data, exec, CMD_NOT_FOUND, token->value);
				data->status = 127;
				break ;
			}
		}
		tmp = tmp->next;
	}
	data->path = path;
}
