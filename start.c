/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:49:32 by tkul              #+#    #+#             */
/*   Updated: 2024/08/13 01:56:22 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_pipes(char *str)
{
	int	quote;
	int	i;
	int	result;

	quote = -1;
	i = -1;
	result = 0;
	while (str[++i])
	{
		ft_set_quote_type(&quote, str[i]);
		if (quote == -1 && str[i] == '|')
		{
			if (is_valid(str) == ERROR)
				return (ft_error(SYNTAX_ERROR), ERROR);
			result++;
		}
	}
	return (result);
}

int	ft_init_tokens(t_data *data)
{
	data->pipe_count = ft_count_pipes(data->cmd);
	if (data->pipe_count == -1)
		return (ERROR);
	data->tokens = (t_token **)malloc(sizeof(t_token *) * (data->pipe_count
				+ 2));
	if (!data->tokens)
		return (ft_error(EXIT_ERROR), ERROR);
	data->tokens[data->pipe_count + 1] = NULL;
	while (data->pipe_count >= 0)
	{
		data->tokens[data->pipe_count] = NULL;
		data->pipe_count--;
	}
	return (SUCCESS);
}

int	ft_run(t_data *data)
{
	char	*temp;

	// int		err;
	if (ft_strlen(data->cmd) > 0 && data->cmd[0] != '\n')
	{
		add_history(data->cmd);
		temp = ft_strtrim(data->cmd, " ");
		if (!temp)
			return (ft_error(EXIT_ERROR), 1);
		free(data->cmd);
		data->cmd = temp;
		if (ft_init_tokens(data) == ERROR)
			return (ERROR);
		if (ft_lexer(data) == ERROR)
			return (-1);
		ft_print_tokens(data->tokens);
		ft_execute(data);
		// if (err == -1)
		// {
		// 	ft_free_tokens(data->tokens);
		// 	return (1);
		// }
	}
	return (SUCCESS);
}

int	ft_start_shell(t_data *data)
{
	while (1)
	{
		if (data->cmd)
			free(data->cmd);
		data->cmd = readline(BHWHT "⭐ MINISHELL> " COLOR_RESET);
		if (!data->cmd)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (ft_run(data) == SUCCESS)
			continue ;
	}
	return (SUCCESS);
}
