/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tugcekul <tugcekul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:11:15 by tkul              #+#    #+#             */
/*   Updated: 2024/08/01 15:18:33 by tugcekul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void remove_index(char **str, int index)
{
	char *s;
	int i;
	int j;

	i = 0;
	j = 0;
	s = malloc(sizeof(char) * (ft_strlen(*str)));
	if (!s)
		return ;
	while ((*str)[i])
	{
		if (i == index)
		{
			i++;
			continue;
		}
		s[j] = (*str)[i];
		i++;
		j++;
	}
	*str = s;
}

char *ft_remove_quote(char *s)
{
	int rm1 = -1;
	int rm2 = -1;
	int i = 0;
	int quote = 0;

	while (s[i])
	{
		if (quote == 0 && (s[i] == '\"' || s[i] == '\''))
		{
			quote = s[i];
			rm1 = i;
		}
		else if (s[i] == quote)
		{
			quote = 0;
			rm2 = i;
		}

		if (rm1 != -1 && rm2 != -1)
		{
			remove_index(&s, rm1);
			remove_index(&s, rm2 - 1);
			rm1 = -1;
			rm2 = -1;
			i = i - 2;
		}
		i++;
	}
	return(s);
}
void check_parser_error(char *str)
{
	int i = 0;

	while(str[i])
	{
		if(str[i] == '|' && str[i+1] == '|')
		{
			printf("Error: syntax error near unexpected token `||'\n");
			exit(1);
		}
		else if(str[i] == '&' && str[i+1] == '&')
		{
			printf("Error: syntax error near unexpected token `&&'\n");
			exit(1);
		}
		i++;
	}
}


