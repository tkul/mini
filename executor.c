/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 23:46:21 by tkul              #+#    #+#             */
/*   Updated: 2024/08/31 03:51:49 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_dup_redictions(t_exec *exec, t_data *data)
{
	if (data->cmd_amount == 1 && exec->in_file && exec->type == CMD_BUILTIN \
		&& exec->in_type != APP_RED)
		return (close(exec->in_fd), 0);
	if (exec->in_file && exec->in_type == IN_RED && !exec->is_here_doc)
	{
		dup2(exec->in_fd, 0);
	}
	else if (exec->in_file && !exec->is_here_doc)
		dup2(exec->in_fd, 0);
	if (exec->out_file)
		dup2(exec->out_fd, 1);
	if (exec->in_fd && exec->is_here_doc)
		dup2(exec->in_fd, 0);
	return (0);
}

char	*find_in_path(char *path, char *cmd)
{
	char	**dirs;
	char	*tmp;
	int		i;

	i = 0;
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

void	ft_execve(t_data *data, t_exec **exec, int i)
{
	int		status;
	pid_t	pid;
	t_token	*token;
	
	token = data->tokens[i];
	(void)exec;
	
	ft_set_path(data,token, exec[i]);
	if (data->path == NULL)
		return ;
	ft_set_args(data,token);
	pid = fork();
	if (!pid)
	{
		if (exec[i]->is_without_cmd)
			mother_close_pipes_all(data);
		ft_dup_redictions(exec[i], data);
		execve(data->path, data->args, data->env);
		exit(0);
	}
	else
	{
		if (WIFEXITED(status))
			data->status = WEXITSTATUS(status);
	}
	waitpid(pid, &status, 0);
}
void	close_pipes_all(int *pipes, int cmd_amount, int i)
{
	int	j;

	j = -1;
	while (++j < cmd_amount * 2)
	{
		if ((i == 0 && j != i * 2 + 1)
			|| (i == cmd_amount - 1 && j != (i - 1) * 2)
			|| (i != 0 && i != cmd_amount - 1 && j != (i - 1) * 2 \
				&& j != i * 2 + 1))
		{
			close(pipes[j]);
		}
	}
}

void	mother_close_pipes_all(t_data *data)
{
	int	j;

	j = 0;
	while (j < data->cmd_amount * 2)
	{
		close(data->pipes[j]);
		j++;
	}
}
static void	ft_run_exec(t_data *data,t_token *token,int cmd_amount, int i, t_exec *exec)
{
	close_pipes_all(data->pipes, cmd_amount, i);
	if (data->check > 0)
	{
		ft_run_builtin(data, i);
		exit(data->status);
	}
	ft_set_path(data, token, exec);
	if (data->path == NULL)
		exit(data->status);
	ft_set_args(data, token);
	if (execve(data->path, data->args, data->env) == -1)
		exit(1);
}
void	ft_run_commands(t_data *data, t_token *token, int i, t_exec *exec)
{
	if (i == 0)
	{
		dup2(data->pipes[i * 2 + 1], 1);
		ft_run_exec(data,token, data->cmd_amount, i, exec);
	}
	else if (i == data->cmd_amount - 1)
	{
		dup2(data->pipes[(i - 1) * 2], 0);
		ft_run_exec(data,token, data->cmd_amount, i, exec);
	}
	else
	{
		dup2(data->pipes[(i - 1) * 2], 0);
		dup2(data->pipes[i * 2 + 1], 1);
		ft_run_exec(data,token, data->cmd_amount, i, exec);
	}
}

void	ft_run_redirects(t_data *data, t_token *token, t_exec *exec, int i)
{
	if (exec->should_run && !exec->is_here_doc)
		ft_run_commands(data,token,i, exec);
	ft_dup_redictions(exec, data);
	ft_init_dupes(data, exec, i);
	if (data->check > 0)
	{
		ft_run_builtin(data, i);
		exit(data->status);
	}
	close_redir_pipe_fd(data, exec, i);
	if (exec->should_run && exec->is_here_doc)
		ft_error(data,ERR_NO_FILE_OR_DIR);
	ft_set_path(data, token, exec);
	if (data->path == NULL)
		exit(data->status);
	ft_set_args(data, token);
	execve(data->path,data->args, data->env);
}

static void	ft_run_pipes(t_data *data, t_exec *exec, int i, t_token *token)
{
	if (exec->type == CMD_WITHOUT_CMD)
	{
		mother_close_pipes_all(data);
		exit(0);
	}
	else if (exec->should_run)
	{
		mother_close_pipes_all(data);
		exit(1);
	}
	else if (!exec->in_type && !exec->out_type)
		ft_run_commands(data,token, i, exec);
	else
		ft_run_redirects(data, token, exec, i);
}

void	ft_exec_part(t_data *data, t_exec *exec, t_token *token)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == 0)
			ft_run_pipes(data, exec, data->index, token);
	data->forks[data->index] = pid;
}

void	ft_run_single_cmd(t_data *data, t_exec **exec, int i)
{
	int	fd1;
	int	fd2;

	if (data->check > 0)
	{
		fd1 = dup(1);
		fd2 = dup(0);
		ft_run_builtin(data, i);
		return(close_redir_fd(data, exec[0], fd1, fd2));
	}
	else
		ft_execve(data, exec, i);
	return ;
}

static void	ft_wait_part(t_data *data)
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

void	ft_start_exec(t_data *data, t_exec **exec,t_token *token, int i)
{
	int 	err;
	t_token *tmp;

	err = 0;
	tmp = token;
	ft_init_here_docs(data, exec, i);
	while(tmp)
	{
		if (tmp->type == CMD)
		{
			if (!exec[i]->type)
				exec[i]->type = ft_find_exec_type(exec, token, i);
		}
		tmp = tmp->next;
	}
	err = ft_exec_init_redirection(data, exec[i], token);
	if (err)
	{
		ft_set_exec_err(data,exec[i], err, token->value);
		return ;
	}
	g_qsignal = 1;
	if (data->cmd_amount > 1)
	{
		if (token->type == CMD || exec[i]->type == CMD_WITHOUT_CMD)
			ft_exec_part(data, exec[data->index], token);
	}
	else
		ft_run_single_cmd(data, exec, i);
	g_qsignal = 0;
}

void	ft_execute(t_data *data)
{
	t_exec	**exec;
	t_token *token;
	int		i;

	i = 0;
	data->index = 0;
	data->cmd_amount = ft_count_cmds(data->tokens);
	if (data->cmd_amount < 0)
			return ;
	exec = malloc(sizeof(t_exec *) * (data->cmd_amount + 1));
	exec[data->cmd_amount] = NULL;
	while (i < data->cmd_amount)
	{
		exec[i] = malloc(sizeof(t_exec));
		ft_init_exec(data, exec[i], data->tokens[i]);
		i++;
	}
	ft_init_pipes(data);
	ft_print_exec_errors(data, exec);
	i = 0;
	while (data->tokens[i])
	{
		data->index = i;
		token = data->tokens[i];
		data->check = ft_is_builtins(token->value);
		data->is_red = ft_is_redirection(token);
		ft_start_exec(data,exec,token,data->index);
		i++;
	}
	if (!(data->check > 0 && data->cmd_amount == 1))
	{
		mother_close_pipes_all(data);
		ft_wait_part(data);
	}
	//ft_print_exec(exec);
}