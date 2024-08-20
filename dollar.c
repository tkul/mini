/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:48:40 by tkul              #+#    #+#             */
/*   Updated: 2024/08/20 21:40:58 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_by_index(char *str, int start, int len)
{
	char	*new_str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	while (str[++i])
	{
		if (i < start || i > start + len)
		{
			new_str[j] = str[i];
			j++;
		}
	}
	new_str[j] = '\0';
	return (new_str);
}

void	add_to_token_buffer(t_data *data, char *value, int index)
{
	char	**arr;
	t_token	*token;
	int		i;

	i = 0;
	arr = ft_split_by_quote(value, ' ');
	if (!arr)
		return ;
	while (arr[i])
	{
		if (value[0] == ' ')
			index = -1;
		token = new_token(ft_strdup(arr[i]), ARG, index);
		if (!token)
			return ;
		token_add_back(&data->token_buffer, token);
		i++;
	}
}

int	process_dollar_variable(t_data *data, char **str, int *i, int quote)
{
	int	j;
	int	index;

	j = (*i) + 1;
	while (ft_isalpha((*str)[j]))
		j++;
	data->lexer->key = ft_substr(*str, (*i) + 1, j - (*i) - 1);
	if (!data->lexer->key)
		return (ERROR);
	data->lexer->value = ft_getenv_by_key(data->lexer->key, data->env);
	if (!data->lexer->value)
	{
		*str = remove_by_index(*str, (*i), j - (*i) - 1);
		(*i)--;
		if (!*str)
			return (ERROR);
	}
	else
	{
		index = (*i);
		if (quote != 0)
			index--;
		*str = remove_by_index(*str, (*i), j - (*i) - 1);
		// (*i) -= ft_strlen(data->lexer->key) - 1;
		add_to_token_buffer(data, data->lexer->value, index);
		(*i)--;
		free(data->lexer->key);
		free(data->lexer->value);
	}
	if (!*str)
		return (ERROR);
	return (SUCCESS);
}
