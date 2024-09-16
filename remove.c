/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:49:23 by tkul              #+#    #+#             */
/*   Updated: 2024/09/04 09:42:09 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_dolllar_handle_helper(t_data *data, char **s, int *i, char *tmp)
{
	char	*status;
	char	*tmp2;

	if ((*s)[*i] == '$' && (*s)[*i + 1] == '?')
	{
		status = ft_itoa(data->status);
		tmp2 = *s;
		tmp = remove_by_index(*s, *i, 1);
		*s = ft_joinstr_index(tmp, status, *i);
		free(tmp);
		free(tmp2);
		free(status);
	}
}

int	ft_dollar_handle(t_data *data, char **s, int *i, int quote)
{
	char	*tmp;

	tmp = NULL;
	if (quote != '\'' && (*s)[*i] == '$')
	{
		data->is_really_env = 1;
		ft_dolllar_handle_helper(data, s, i, tmp);
		if ((*s)[*i] == '$' && ft_isalphaaa((*s)[*i + 1]))
		{
			if (process_dollar_variable(data, s, i, quote) == ERROR)
				return (ERROR);
		}
		else if (quote == 0 && (*s)[*i] == '$' && ((*s)[*i + 1] == '"'
				|| (*s)[*i + 1] == '\''))
		{
			tmp = *s;
			*s = remove_by_index(tmp, *i, 0);
			free(tmp);
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

	data->is_really_env = 0;
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
