/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 23:46:21 by tkul              #+#    #+#             */
/*   Updated: 2024/08/28 20:32:58 by tkul             ###   ########.fr       */
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
	
	if (data->control != 0)
		ft_set_path(data,token);
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
static void	ft_run_exec(t_data *data, int cmd_amount, int i)
{
	close_pipes_all(data->pipes, cmd_amount, i);
	if (data->check > 0)
	{
		ft_run_builtin(data, i);
		exit(data->status);
	}
	if (execve(data->path, data->args, data->env) == -1)
		exit(1);
}
void	ft_run_commands(t_data *data, int i)
{
	if (i == 0)
	{
		dup2(data->pipes[i * 2 + 1], 1);
		ft_run_exec(data,data->cmd_amount, i);
	}
	else if (i == data->cmd_amount - 1)
	{
		dup2(data->pipes[(i - 1) * 2], 0);
		ft_run_exec(data, data->cmd_amount, i);
	}
	else
	{
		dup2(data->pipes[(i - 1) * 2], 0);
		dup2(data->pipes[i * 2 + 1], 1);
		ft_run_exec(data, data->cmd_amount, i);
	}
}

void	ft_run_redirects(t_data *data, t_exec *exec, int i)
{
	if (exec->should_run && !exec->is_here_doc)
		ft_run_commands(data, i);
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
	execve(data->path,data->args, data->env);
}

static void	ft_run_pipes(t_data *data, t_exec *exec, int i, t_token *token)
{
	ft_set_path(data, token);
	ft_set_args(data, token);
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
		ft_run_commands(data, i);
	else
		ft_run_redirects(data, exec, i);
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

	// if (exec[0]->should_run && !exec[0]->is_here_doc)
	// 	return ;
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

static int	ft_for_in_file(t_data *data ,t_exec *exec)
{
	if (!access(exec->in_file, F_OK) && access(exec->in_file, R_OK) == -1)
	{
		exec->should_run = 1;
		if (!exec->is_here_doc)
			ft_error(data, ERR_PERMISSION_DENIED);
		return (126);
	}
	exec->should_run = 1;
	if (exec->is_here_doc)
		return (0);
	// ft_set_exec_err(exec, ERR_NO_FILE_OR_DIR, exec->in_file);
	return (ERR_NO_FILE_OR_DIR);
}

static int	ft_for_out_file(t_data *data, t_exec *exec)
{
	if (!access(exec->out_file, F_OK) && access(exec->out_file, W_OK) == -1)
	{
		exec->should_run = 1;
		ft_error(data, ERR_PERMISSION_DENIED);
		return (1);
	}
	exec->should_run = 1;
	// ft_set_exec_err(exec, ERR_NO_FILE_OR_DIR, exec->out_file);
	return (ERR_NO_FILE_OR_DIR);
}

int	ft_open_check_files(t_exec *exec, int status, t_data *data)
{
	if (exec->in_file || exec->is_here_doc)
	{
		if (exec->in_type == IN_RED && exec->should_run == 0)
			exec->in_fd = open(exec->in_file, O_RDONLY);
		else if (exec->in_type == HER_DOC)
		{
			exec->heredocs[exec->here_doc_idx] = ft_strdup(exec->in_file);
			exec->here_doc_idx++;
		}
		if (exec->in_fd == -1 && exec->should_run == 0)
			return (ft_for_in_file(data,exec));
	}
	if (exec->out_file && exec->should_run == 0)
	{
		if (exec->out_type == OUT_RED)
			exec->out_fd = open(exec->out_file, \
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (exec->out_type == APP_RED)
			exec->out_fd = open(exec->out_file, \
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (exec->out_fd == -1 && exec->should_run == 0)
			return (ft_for_out_file(data, exec));
	}
	return (status);
}

int	ft_init_redirection(t_data *data, t_exec *exec, t_token *token)
{
	int		i;
	int 	j;

	i = 0;
	j = 0;
	exec->heredocs = malloc(sizeof(char *) * (exec->count_heredocs + 1));
	exec->heredocs[exec->count_heredocs] = NULL;
	while (token)
	{
		if (ft_is_redirection_single(token) && token->next)
		{
			if (token->type == IN_RED || token->type == HER_DOC)
			{
				exec->in_type = token->type;
				exec->in_file = ft_strdup(token->next->value);
			}
			else if (token->type == OUT_RED || token->type == APP_RED)
			{
				exec->out_type = token->type;
				exec->out_file = ft_strdup(token->next->value);
			}
			i = ft_open_check_files(exec, i, data);
		}
		token = token->next;
	}
	return (i);
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
	err = ft_init_redirection(data, exec[i], token);
	g_qsignal = 1;
	if (data->cmd_amount > 1)
	{
		if (token->type == CMD || exec[i]->type == CMD_WITHOUT_CMD)
		{
			ft_exec_part(data, exec[data->index], token);
		}
	}
	else
	{
		ft_run_single_cmd(data, exec, i);
	}
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
	// ft_print_exec(exec);
	ft_init_pipes(data);
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
	mother_close_pipes_all(data);
	ft_wait_part(data);
}