/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:40:58 by tkul              #+#    #+#             */
/*   Updated: 2024/09/03 00:54:32 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_quote_type(int *quote, char c)
{
	if (*quote == -1 && (c == '\'' || c == '\"'))
		*quote = (int)c;
	else if (*quote == (int)(c))
		*quote = -1;
}

int	count_word(const char *str, char c)
{
	int	i;
	int	count;
	int	quote;
	int	toggle;

	i = -1;
	count = 0;
	quote = -1;
	toggle = 0;
	while (str[++i])
	{
		ft_set_quote_type(&quote, str[i]);
		if (quote == -1 && str[i] == c)
			toggle = 0;
		else if (quote == -1 && toggle == 0)
		{
			toggle = 1;
			count++;
		}
	}
	return (count);
}

int	ft_isalphaaa(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
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
	{
		write(2, "⭐MINISHELL> unclosed quotes\n", 30);
		return (ERROR);
	}
	return (SUCCESS);
}
