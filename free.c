/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:28:23 by tkul              #+#    #+#             */
/*   Updated: 2024/09/02 18:41:40 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tokens(t_token **tokens)
{
	t_token	**tmp;
	t_token	*next;
	t_token	*tmp2;
	int		i;

	if (!tokens || !*tokens)
		return ;
	tmp = tokens;
	i = 0;
	while (tmp[i])
	{
		next = tmp[i];
		while (next)
		{
			tmp2 = next;
			next = next->next;
			free(tmp2->value);
			free(tmp2);
		}
		i++;
	}
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_free_data(t_data *data)
{
	if (data->path)
	{
		free(data->path);
		data->path = NULL;
	}
	if (data->args)
	{
		ft_free_array(data->args);
		data->args = NULL;
	}
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
	if (data->pipes)
	{
		free(data->pipes);
		data->pipes = NULL;
	}
}

void	free_exec_data(t_data *data, t_exec **exec, int cmd_amount)
{
	int	i;

	i = 0;
	while (i < cmd_amount)
	{
		if (exec[i]->is_here_doc)
		{
			free(exec[i]->is_here_doc);
			exec[i]->is_here_doc = NULL;
		}
		if (exec[i]->out_file)
		{
			free(exec[i]->out_file);
			exec[i]->out_file = NULL;
		}
		if (exec[i]->in_file)
		{
			free(exec[i]->in_file);
			exec[i]->in_file = NULL;
		}
		free(exec[i]);
		exec[i] = NULL;
		i++;
	}
	ft_free_data(data);
}

int	ft_parser_free(t_data *data)
{
	ft_free_array(data->cmds);
	if (data->lexer->value)
		free(data->lexer->value);
	if (data->lexer->key)
		free(data->lexer->key);
	if (ft_control_token(data, data->tokens) == ERROR)
		return (free(data->lexer), ERROR);
	free(data->lexer);
	return (SUCCESS);
}
