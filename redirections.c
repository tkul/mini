/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:49:17 by tkul              #+#    #+#             */
/*   Updated: 2024/08/12 21:46:03 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_by_index(char **str, char c, int start)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(*str) + 2));
	if (!new_str)
		return ;
	while ((*str)[i])
	{
		if (i == start)
		{
			new_str[j] = c;
			j++;
		}
		new_str[j] = (*str)[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	free(*str);
	*str = new_str;
}

int	ft_init_redirections(t_data *data)
{
	int	i;
	int	quote;

	i = 0;
	quote = -1;
	while ((data->cmd)[i])
	{
		ft_set_quote_type(&quote, (data->cmd)[i]);
		if (quote == -1 && (data->cmd)[i] == '<' && (data->cmd)[i + 1] == '<')
		{
			add_by_index(&(data->cmd), ' ', i);
			add_by_index(&(data->cmd), ' ', i + 3);
			i += 3;
		}
		else if (quote == -1 && (data->cmd)[i] == '<')
		{
			add_by_index(&(data->cmd), ' ', i);
			add_by_index(&(data->cmd), ' ', i + 2);
			i += 2;
		}
		else if (quote == -1 && (data->cmd)[i] == '>' && (data->cmd)[i
			+ 1] == '>')
		{
			add_by_index(&(data->cmd), ' ', i);
			add_by_index(&(data->cmd), ' ', i + 3);
			i += 3;
		}
		else if (quote == -1 && (data->cmd)[i] == '>')
		{
			add_by_index(&(data->cmd), ' ', i);
			add_by_index(&(data->cmd), ' ', i + 2);
			i += 2;
		}
		else
			i++;
	}
	return (SUCCESS);
}

int	is_redirection(char *str)
{
	int	i;
	int	quote;

	i = -1;
	quote = -1;
	while (str[++i])
	{
		ft_set_quote_type(&quote, str[i]);
		if (quote == -1 && ft_strcmp(str, "<<") == 0)
			return (HER_DOC);
		if (quote == -1 && ft_strcmp(str, ">>") == 0)
			return (APP_RED);
		if (quote == -1 && ft_strcmp(str, "<") == 0)
			return (IN_RED);
		if (quote == -1 && ft_strcmp(str, ">") == 0)
			return (OUT_RED);
	}
	return (-1);
}
