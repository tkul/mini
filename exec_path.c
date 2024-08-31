/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 11:15:02 by tkul              #+#    #+#             */
/*   Updated: 2024/08/31 15:51:23 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_in_path(char *path, char *cmd)
{
	char	**dirs;
	char	*tmp;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);	
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		tmp = ft_strjoin(tmp, cmd);
		if (access(tmp, F_OK) == 0)
		{
			ft_free_array(dirs);
			return (tmp);
		}
		i++;
	}
	ft_free_array(dirs);
	return (NULL);
}

int ft_find_absolute_path(t_data *data ,t_token *token, t_exec *exec)
{
	struct stat	buf;

	stat(token->value, &buf);
	if (access(data->path, F_OK) == -1)
		return (ft_set_exec_err(data,exec, ERR_NO_SUCH_FILE, token->value),127);
	if (errno == EACCES)
		return (ft_set_exec_err(data,exec, ERR_PERMISSION_DENIED, token->value),1);
	if (S_ISDIR(buf.st_mode))
		return (ft_set_exec_err(data,exec, ERR_IS_DIR, token->value),126);
	if (access(data->path, X_OK) == -1)
		return (ft_set_exec_err(data, exec,ERR_PERMISSION_DENIED2, token->value), 126);
	return (0);
}

void    ft_set_path(t_data *data, t_token *token, t_exec *exec)
{
	t_token *tmp;
	
	tmp = token;
    while (tmp)
	{
		if (tmp->type == CMD)
		{
			data->path = find_in_path(ft_getenv_by_key("PATH", data->env),
			tmp->value);
			if (data->path)
			{
				if (!ft_find_absolute_path(data, tmp, exec))
					break ;
			}
			else
			{
				ft_set_exec_err(data, exec,CMD_NOT_FOUND, token->value);
				break ;
			}
		}
		tmp = tmp->next;
	}
	// while (token && token->type != CMD)
	// 	token = token->next;
	// if (data->path == NULL)
	// {
	// 	write(2, "minishell: ", 11);
	// 	write(2, token->value, ft_strlen(token->value));
	// 	write(2, ": command not found\n", 20);
	// 	data->status = 127;
	// 	return ;
	// }
}