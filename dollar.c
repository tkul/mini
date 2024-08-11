/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:48:40 by tkul              #+#    #+#             */
/*   Updated: 2024/08/11 15:11:02 by tkul             ###   ########.fr       */
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

int	process_dollar_variable(t_data *data, char **str, int i)
{
	int	j;

	j = i + 1;
	while (ft_isalpha((*str)[j]))
		j++;
	data->lexer->key = ft_substr(*str, i + 1, j - i - 1);
	if (!data->lexer->key)
		return (ERROR);
	data->lexer->value = ft_getenv_by_key(data->lexer->key, data->env);
	if (!data->lexer->value)
		*str = remove_by_index(*str, i, j - i - 1);
	else
	{
		*str = remove_by_index(*str, i, j - i - 1);
		*str = ft_joinstr_index(*str, data->lexer->value, i);
		free(data->lexer->key);
		free(data->lexer->value);
	}
	if (!*str)
		return (ERROR);
	return (SUCCESS);
}

int	handle_dollar(t_data *data, char **str)
{
	int		i;
	int		quote;
	char	*status;

	i = -1;
	quote = -1;
	while ((*str)[++i])
	{
		ft_set_quote_type(&quote, (*str)[i]);
		if (quote != '\'' && (*str)[i] == '$')
		{
			if ((*str)[i] == '$' && (*str)[i + 1] == '?')
			{
				status = ft_itoa(data->status);
				*str = remove_by_index(*str, i, 1);
				*str = ft_joinstr_index(*str, status, i);
			}
			else if ((*str)[i] == '$' && ft_isalpha((*str)[i + 1]))
			{
				if (process_dollar_variable(data, str, i) == ERROR)
					return (ERROR);
			}
			if ((*str)[i] == 0)
				break ;
		}
	}
	return (SUCCESS);
}
