/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:14:09 by tkul              #+#    #+#             */
/*   Updated: 2024/08/14 11:09:20 by tkul             ###   ########.fr       */
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

int	ft_control_token(t_data *data, t_token **token)
{
	t_token	*current;

	current = *token;
	while (current)
	{
		if (current->type == IN_RED || current->type == OUT_RED
			|| current->type == APP_RED || current->type == HER_DOC)
		{
			if (current->next == NULL)
				return (ft_error(data, SYNTAX_ERROR), ERROR);
		}
		current = current->next;
	}
	return (SUCCESS);
}
