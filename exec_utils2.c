/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:26:10 by tkul              #+#    #+#             */
/*   Updated: 2024/08/27 04:18:43 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_find_absolute_path(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (1);
	return (0);
}

void    ft_set_path(t_data *data, t_exec **exec, t_token *token)
{
    (void)exec;
	t_token *tmp;
	
	tmp = token;
    while(tmp)
	{
		if (tmp->type == CMD)
		{
			data->path = find_in_path(ft_getenv_by_key("PATH", data->env),
			tmp->value);
			if (data->path == NULL)
			{
				if (ft_find_absolute_path(tmp->value))
				{
					data->path = ft_strdup(tmp->value);
					break ;
				}
			}
		}
		tmp = tmp->next;
	}
	while (token && token->type != CMD)
		token = token->next;
	if (data->path == NULL)
	{
		write(2, "⭐MINISHELL> ", 13);
		write(2, token->value, ft_strlen(token->value));
		write(2, ": command not found\n", 21);
		data->status = CMD_NOT_FOUND;
		return ;
	}
}

void    ft_set_args(t_data *data, t_exec **exec, t_token *token)
{
    (void)exec;
	int		args_len;
    int j;
	t_token *tmp;
    
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
	t_token *tmp;

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

int	ft_count_cmds(t_token **tokens)
{
	int		amount;
	int		i;
	t_token *tmp;
	int red_count;
	int flag;

	i = -1;
	amount = 0;
	flag = 0;
	red_count = ft_is_redirect_without_cmd(tokens);
	while (tokens[++i])
	{
		tmp = tokens[i];
		while (tmp)
		{
			if (tmp->type == CMD)
			{
				flag = 1;
				amount++;
			}
			tmp = tmp->next;
		}
	}
	if (red_count > 0 && flag == 0)
		return (1);
	return (amount);
}
