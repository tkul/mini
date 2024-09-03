/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:28:43 by tkul              #+#    #+#             */
/*   Updated: 2024/09/03 13:31:37 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_part(t_data *data, t_exec *exec, t_token *token)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		ft_run_pipes(data, exec, data->index, token);
	data->forks[data->index] = pid;
}

void	ft_wait_part(t_data *data)
{
	int	i;

	i = data->cmd_amount - 1;
	while (i >= 0)
	{
		if (i == data->cmd_amount - 1)
		{
			waitpid(data->forks[i], &data->status, 0);
			if (WIFEXITED(data->status))
				data->status = WEXITSTATUS(data->status);
		}
		waitpid(data->forks[i], NULL, 0);
		i--;
	}
}

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
