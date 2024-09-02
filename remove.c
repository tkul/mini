/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:49:23 by tkul              #+#    #+#             */
/*   Updated: 2024/09/03 00:53:59 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_quote(t_data *data, char *s, int *quote, int i)
{
	if (*quote == 0 && (s[i] == '\"' || s[i] == '\''))
	{
		*quote = s[i];
		data->rm1 = i;
	}
	else if (s[i] == *quote)
	{
		*quote = 0;
		data->rm2 = i;
	}
}

int	ft_dollar_handle(t_data *data, char **s, int *i, int quote)
{
	char	*status;

	if (quote != '\'' && (*s)[*i] == '$')
	{
		if ((*s)[*i] == '$' && (*s)[*i + 1] == '?')
		{
			status = ft_itoa(data->status);
			*s = remove_by_index(*s, *i, 1);
			*s = ft_joinstr_index(*s, status, *i);
		}
		else if ((*s)[*i] == '$' && ft_isalphaaa((*s)[*i + 1]))
		{
			if (process_dollar_variable(data, s, i, quote) == ERROR)
				return (ERROR);
		}
		else if (quote == 0 && (*s)[*i] == '$' && ((*s)[*i + 1] == '"'
				|| (*s)[*i + 1] == '\''))
		{
			*s = remove_by_index(*s, *i, *i - 1);
			*i = *i - 1;
		}
	}
	return (SUCCESS);
}

void	ft_helper_remove(t_data *data, char **s, int *i)
{
	if (data->rm1 != -1 && data->rm2 != -1)
	{
		remove_index(s, data->rm1);
		remove_index(s, data->rm2 - 1);
		data->rm1 = -1;
		data->rm2 = -1;
		*i = *i - 2;
	}
}

int	ft_remove_quotes(t_data *data, char **s)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	data->rm1 = -1;
	data->rm2 = -1;
	if (ft_control_quotes(*s) == ERROR)
		return (ERROR);
	while ((*s)[i])
	{
		ft_quote(data, *s, &quote, i);
		if (ft_dollar_handle(data, s, &i, quote) == ERROR)
			return (ERROR);
		ft_helper_remove(data, s, &i);
		i++;
		if (!*s)
			break ;
	}
	return (SUCCESS);
}
