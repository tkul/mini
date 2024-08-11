/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:49:23 by tkul              #+#    #+#             */
/*   Updated: 2024/08/11 15:11:39 by tkul             ###   ########.fr       */
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

int	ft_remove_quotes(char **s)
{
	int	i;
	int	quote;
	int	rm1;
	int	rm2;

	i = -1;
	quote = 0;
	rm1 = -1;
	rm2 = -1;
	if (ft_control_quotes(*s) == ERROR)
		return (ERROR);
	while ((*s)[++i])
	{
		if (quote == 0 && ((*s)[i] == '\"' || (*s)[i] == '\''))
		{
			quote = (*s)[i];
			rm1 = i;
		}
		else if ((*s)[i] == quote)
		{
			quote = 0;
			rm2 = i;
		}
		if (rm1 != -1 && rm2 != -1)
		{
			remove_index(s, rm1);
			remove_index(s, rm2 - 1);
			rm1 = -1;
			rm2 = -1;
			i = i - 2;
		}
	}
	return (SUCCESS);
}
