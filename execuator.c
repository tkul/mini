/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execuator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 23:46:21 by tkul              #+#    #+#             */
/*   Updated: 2024/08/23 02:17:29 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_cmds(t_token **tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == CMD)
			count++;
		i++;
	}
	return (count);
}

char	*find_in_path(char *path, char *cmd)
{
	char	**dirs;
	char	*tmp;
	int		i;

	i = 0;
	dirs = ft_split(path, ':');
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

void	ft_execve(t_data *data, int i)
{
	char	*path;
	char	**args;
	int		status;
	pid_t		pid;
	int		args_len;
	int		j;
	t_token	*tokens;

	path = find_in_path(ft_getenv_by_key("PATH", data->env),
			data->tokens[i]->value);
	if (path == NULL)
	{
		write(2, "⭐MINISHELL> ", 13);
        write(2, data->tokens[i]->value, ft_strlen(data->tokens[i]->value));
        write(2, ": command not found\n", 21);
		data->status = CMD_NOT_FOUND;
		return ;
	}
	tokens = data->tokens[i];
	args_len = 0;
	while (tokens)
	{
		if (tokens->type == ARG)
			args_len++;
		tokens = tokens->next;
	}
	args = malloc(sizeof(char *) * (args_len + 2));
	args[args_len + 1] = NULL;
	j = 1;
	args[0] = ft_strdup(path);
	tokens = data->tokens[i];
	while (tokens)
	{
		if (tokens->type == ARG)
		{
			args[j] = ft_strdup(tokens->value);
			j++;
		}
		tokens = tokens->next;
	}
	pid = fork();
	if (pid == 0)
	{
		execve(path, args, data->env);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data->status = WEXITSTATUS(status);
	}
}

void	ft_execute(t_data *data)
{
	t_exec	**exec;
	int		i;

	i = 0;
	data->cmd_amount = ft_count_cmds(data->tokens);
	data->check = ft_is_builtins(data->tokens[i]->value);
	exec = malloc(sizeof(t_exec *) * (data->cmd_amount + 1));
	exec[data->cmd_amount] = NULL;
	while (data->tokens[i])
	{
		if (data->check > 0 && data->cmd_amount == 1)
		{
			if (ft_strcmp(data->tokens[i]->value, "pwd") == 0)
				ft_pwd(data);
			else if (ft_strcmp(data->tokens[i]->value, "echo") == 0)
				ft_echo(data, &i);
			else if (ft_strcmp(data->tokens[i]->value, "env") == 0)
				ft_env(data);
			else if (ft_strcmp(data->tokens[i]->value, "exit") == 0)
				ft_exit(data, &i);
			else if (ft_strcmp(data->tokens[i]->value, "cd") == 0)
				ft_cd(data, &i);
			else if (ft_strcmp(data->tokens[i]->value, "export") == 0)
				ft_export(data, &i);
			else if (ft_strcmp(data->tokens[i]->value, "unset") == 0)
				ft_unset(data, &i);
		}
		else
			ft_execve(data, i);
		i++;
	}
}
