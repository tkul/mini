/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:43:39 by ayirmili          #+#    #+#             */
/*   Updated: 2024/08/24 01:22:34 by ayirmili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static void	fork_exec(t_data *data, t_token **tokens, int i)
{
    // printf("tokens[i] %s\n", tokens[i]->value);

    (void)data;
	// data->path = find_path(data, tokens[i]);
	
}

void	pipe_fork(t_data *data, int i, t_token **tokens)
{
    handle_pipe_dup(data, i);
    if (check_direct(data, tokens))
		exit(1);
    // if (check_builtin(data &i) == 1)
		
    fork_exec(data, tokens, i);
}

int ft_create_pipe(t_data *data)
{    
    int i;
    
    i = -1;
    data->pipe_fd = malloc(sizeof(int) * (data->pipe_count * 2));
    data->pid = malloc(sizeof(int) * (data->cmd_amount));
    if (! data->pipe_fd)
		return (perror("Minishell: malloc error"), ERROR);

    while(++i < data->pipe_count)
    {
        if (pipe(data->pipe_fd + i * 2) == -1)
			return (perror("Minishell: pipe error"), ERROR);
    }

    return (SUCCESS);
}

int ft_pipe(t_data *data, t_token **tokens)
{
    int	i;

	i = -1;
	if (ft_create_pipe(data) == ERROR)
		return (ERROR);
    while (++i < data->cmd_amount)
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			return (ERROR);
		else if (data->pid[i] == 0)
			pipe_fork(data, i, tokens);
	}

    return (close_fd(data));
}


void    ft_run_multiple_command(t_data *data)
{
    t_token **tokens;

    printf("pipe_count %d\n", data->pipe_count);

    tokens = data->tokens;
    data->cleaned_cmd = clear_quotes(data->cmd);
    
    ft_pipe(data, tokens);
}
