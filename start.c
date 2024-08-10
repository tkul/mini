/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:49:32 by tkul              #+#    #+#             */
/*   Updated: 2024/08/10 15:32:11 by tkul             ###   ########.fr       */
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
			if (str[i] == '|' && str[i + 1] == '|')
				return (printf("Error: syntax error near unexpected token `||'\n"),
					-1);
			if (str[i + 1] == '\0')
				return (printf("Error: syntax error near unexpected token `|'\n"),
					-1);
			result++;
		}
	}
	return (result);
}

int	ft_init_tokens(t_data *data)
{
	data->pipe_count = ft_count_pipes(data->cmd);
	if (data->pipe_count == -1)
		return (-1);
	data->tokens = (t_token **)malloc(sizeof(t_token *) * (data->pipe_count
				+ 2));
	if (!data->tokens)
		return (-1);
	data->tokens[data->pipe_count + 1] = NULL;
	while (data->pipe_count >= 0)
	{
		data->tokens[data->pipe_count] = NULL;
		data->pipe_count--;
	}
	return (0);
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
			return (1);
		free(data->cmd);
		data->cmd = temp;
		if (ft_init_tokens(data) == -1)
			return (1);
		if (ft_lexer(data) == -1)
			return (-1);
		printf("------------\n");
		ft_print_tokens(data->tokens);
		// if (err == -1)
		// {
		// 	ft_free_tokens(data->tokens);
		// 	return (1);
		// }
	}
	return (0);
}

int	ft_start_shell(t_data *data)
{
	while (1)
	{
		if (data->cmd)
			free(data->cmd);
		data->cmd = readline(BHWHT "⭐ MINISHELL> " COLOR_RESET);
		if (!data->cmd)
			break ;
		if (ft_run(data) == 1)
			continue ;
	}
	return (0);
}