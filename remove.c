/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:49:23 by tkul              #+#    #+#             */
/*   Updated: 2024/08/23 18:58:49 by tkul             ###   ########.fr       */
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
		return (printf("Error: unclosed quotes\n"), ERROR);
	return (SUCCESS);
}

int	ft_set_env_varibles(t_data *data, char **s)
{
	int		i;
	int		quote;
	// int		rm1;
	// int		rm2;
	char	*status;

	i = 0;
	quote = 0;
	// rm1 = -1;
	// rm2 = -1;
	if (ft_control_quotes(*s) == ERROR)
		return (ERROR);
	while ((*s)[i])
	{
		if (quote == 0 && ((*s)[i] == '\"' || (*s)[i] == '\''))
		{
			quote = (*s)[i];
			// rm1 = i;
		}
		else if ((*s)[i] == quote)
		{
			quote = 0;
			// rm2 = i;
		}
		if (quote != '\'' && (*s)[i] == '$')
		{
			if ((*s)[i] == '$' && (*s)[i + 1] == '?')
			{
				status = ft_itoa(data->status);
				*s = remove_by_index(*s, i, 1);
				*s = ft_joinstr_index(*s, status, i);
			}
			else if ((*s)[i] == '$' && ft_isalpha((*s)[i + 1]))
			{
				if (process_dollar_variable(data, s, &i, quote) == ERROR)
					return (ERROR);
			}
		}
		// if (rm1 != -1 && rm2 != -1)
		// {
		// 	remove_index(s, rm1);
		// 	remove_index(s, rm2 - 1);
		// 	rm1 = -1;
		// 	rm2 = -1;
		// 	i = i - 2;
		// }
		i++;
		if (!*s)
			break ;
	}
	return (SUCCESS);
}
