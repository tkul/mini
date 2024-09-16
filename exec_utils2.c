/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tugcekul <tugcekul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:26:10 by tkul              #+#    #+#             */
/*   Updated: 2024/09/08 20:58:58 by tugcekul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_args(t_data *data, t_token *token)
{
	int		args_len;
	int		j;
	t_token	*tmp;

	args_len = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == ARG)
			args_len++;
		tmp = tmp->next;
	}
	data->args = malloc(sizeof(char *) * (args_len + 2));
	data->args[args_len + 1] = NULL;
	j = 1;
	data->args[0] = ft_strdup(data->path);
	while (token)
	{
		if (token->type == ARG)
		{
			data->args[j] = ft_strdup(token->value);
			j++;
		}
		token = token->next;
	}
}

int	ft_is_redirect_without_cmd(t_token **tokens)
{
	int		i;
	int		red_count;
	t_token	*tmp;

	i = 0;
	red_count = 0;
	while (tokens[i])
	{
		tmp = tokens[i];
		while (tmp)
		{
			if (tmp->type == CMD)
				break ;
			if (ft_is_redirection_single(tmp))
				red_count++;
			tmp = tmp->next;
		}
		i++;
	}
	return (red_count);
}

int	ft_count_amount(t_token *tmp, t_data *data, int amount)
{
	(void)data;
	while (tmp)
	{
		if (tmp->type == CMD)
			amount++;
		tmp = tmp->next;
	}
	return (amount);
}

int	ft_count_cmds(t_data *data, t_token **tokens)
{
	int		amount;
	int		i;
	t_token	*tmp;
	int		red_count;

	i = -1;
	amount = 0;
	red_count = ft_is_redirect_without_cmd(tokens);
	while (tokens[++i])
	{
		tmp = tokens[i];
		amount = ft_count_amount(tmp, data, amount);
	}
	if (red_count > 0 && data->pipe_count == 0)
		return (1);
	else if (red_count > 0 && data->pipe_count > 0)
		return (1 + data->pipe_count);
	return (amount);
}

int	ft_count_heredocs(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == HER_DOC)
			count++;
		token = token->next;
	}
	return (count);
}
