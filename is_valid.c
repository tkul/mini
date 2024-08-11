/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:14:09 by tkul              #+#    #+#             */
/*   Updated: 2024/08/11 16:17:49 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid(char *str)
{
	int	quote;
	int	i;

	quote = -1;
	i = -1;
	while (str[++i])
	{
		ft_set_quote_type(&quote, str[i]);
		if (quote == -1 && str[0] == '|')
			return (ERROR);
		if (quote == -1 && str[i] == '|')
		{
			if (str[i + 1] == '\0')
				return (ERROR);
		}
		if (quote == -1 && str[i] == '|')
		{
			while (str[i + 1] == ' ')
				i++;
			if (str[i + 1] == '|')
				return (ERROR);
		}
	}
	return (SUCCESS);
}
//ft_control_red tam olarak doğre çalışmıyor düzenlenecek

// int	ft_control_red(char *str)
// {
// 	int	quote;
// 	int	i;

// 	quote = -1;
// 	i = -1;
// 	while (str[++i])
// 	{
// 		ft_set_quote_type(&quote, str[i]);
// 		if (quote == -1 && (str[i] == '<' || str[i] == '>'))
// 		{
// 			if (str[i + 1] == '\0')
// 				return (ERROR);
// 		}
// 		if (quote == -1 && (str[i] == '<' || str[i] == '>'))
// 		{
// 			while (str[i + 1] == ' ')
// 				i++;
// 			if (str[i + 1] == '<' || str[i + 1] == '>')
// 				return (ERROR);
// 		}
// 		else
// 			break ;
// 	}
// 	return (SUCCESS);
// }
