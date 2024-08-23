/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:03:18 by ayirmili          #+#    #+#             */
/*   Updated: 2024/08/24 01:14:42 by ayirmili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quote_count(const char *cmd)
{
	int	len = 0;
	while (*cmd)
	{
		if (*cmd != '"')
			len++;
		cmd++;
	}
	return (len);
}

char	*clear_quotes(char *cmd)
{
	int		i = 0;
	int		j = 0;
	char	*cleaned = (char *)malloc(sizeof(char) * (quote_count(cmd) + 1));
	if (!cleaned)
		return (NULL);
	while (cmd[i])
	{
		if (cmd[i] != '"')
			cleaned[j++] = cmd[i];
		i++;
	}
	cleaned[j] = '\0';
	return (cleaned);
}

void	handle_pipe_dup(t_data *data, int i)
{
	int	j;

	j = -1;
	// handle_heredoc_dup(data, i);
	if (i != data->pipe_count)
	{
		if (dup2(data->pipe_fd[i * 2 + 1], STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 error (stdout)");
			exit(1);
		}
	}
	while (++j < data->pipe_count* 2)
		close(data->pipe_fd[j]);
}
int	check_direct(t_data *data, t_token **tokens)
{
	(void)data;
	(void)tokens;
	// TODO bu fonsiyon redirectionlar geldiğinde kurulacak fonksiyon
	return (0);
}

int	close_fd(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->pipe_count * 2)
		close(data->pipe_fd[i]);
	i = -1;
	while (++i < data->pipe_count + 1)
	{
		waitpid(data->pid[i], &data->status, 0);
		data->status = WEXITSTATUS(data->status);
	}
	free(data->pipe_fd);
	free(data->pid);
	return (SUCCESS);
}