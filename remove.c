/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:49:23 by tkul              #+#    #+#             */
/*   Updated: 2024/09/02 19:12:26 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_control_quotes(char *s)
{
	int	i;
	int	quote;
	int	quote2;

	i = -1;
	quote = 0;
	quote2 = 0;
	while (s[++i])
	{
		if (quote == 0 && (s[i] == '\"' || s[i] == '\''))
			quote = s[i];
		else if (s[i] == quote)
			quote = 0;
		if (quote2 == 0 && (s[i] == '\"' || s[i] == '\''))
			quote2 = s[i];
		else if (s[i] == quote2)
			quote2 = 0;
	}
	if (quote != 0 || quote2 != 0)
	{
		write(2, "⭐MINISHELL> unclosed quotes\n", 30);
		return (ERROR);
	}
	return (SUCCESS);
}

static void	remove_index(char **s, int index)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(*s)));
	if (!new_str)
		return ;
	while ((*s)[i])
	{
		if (i == index)
		{
			i++;
			continue ;
		}
		new_str[j] = (*s)[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	free(*s);
	*s = new_str;
}

int	ft_remove_quotes(t_data *data, char **s)
{
	int		i;
	int		quote;
	char	*status;

	i = 0;
	quote = 0;
	data->rm1 = -1;
	data->rm2 = -1;
	if (ft_control_quotes(*s) == ERROR)
		return (ERROR);
	while ((*s)[i])
	{
		if (quote == 0 && ((*s)[i] == '\"' || (*s)[i] == '\''))
		{
			quote = (*s)[i];
			data->rm1 = i;
		}
		else if ((*s)[i] == quote)
		{
			quote = 0;
			data->rm2 = i;
		}
		if (quote != '\'' && (*s)[i] == '$')
		{
			if ((*s)[i] == '$' && (*s)[i + 1] == '?')
			{
				status = ft_itoa(data->status);
				*s = remove_by_index(*s, i, 1);
				*s = ft_joinstr_index(*s, status, i);
			}
			else if ((*s)[i] == '$' && ft_isalphaaa((*s)[i + 1]))
			{
				if (process_dollar_variable(data, s, &i, quote) == ERROR)
					return (ERROR);
			}
			else if (quote == 0 && (*s)[i] == '$' && ((*s)[i + 1] == '"'
					|| (*s)[i + 1] == '\''))
			{
				*s = remove_by_index(*s, i, i - 1);
				i--;
			}
		}
		if (data->rm1 != -1 && data->rm2 != -1)
		{
			remove_index(s, data->rm1);
			remove_index(s, data->rm2 - 1);
			data->rm1 = -1;
			data->rm2 = -1;
			i = i - 2;
		}
		i++;
		if (!*s)
			break ;
	}
	return (SUCCESS);
}
