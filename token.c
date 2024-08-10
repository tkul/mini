/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:49:39 by tkul              #+#    #+#             */
/*   Updated: 2024/08/10 15:41:40 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_add_back(t_token **token, t_token *new)
{
	t_token	*current;

	if (!token)
		return ;
	if (!*token)
	{
		*token = new;
		return ;
	}
	current = *token;
	while (current->next)
		current = current->next;
	current->next = new;
	new->prev = current;
}

t_token	*new_token(char *value, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*get_last_token(t_token *token)
{
	t_token	*current;

	current = token;
	if (!current)
		return (NULL);
	while (current->next)
		current = current->next;
	return (current);
}

void	ft_create_token(t_data *data, char *str, int i, int j)
{
	t_token	*new;
	t_token	*last;
	int		red;

	red = is_redirection(str);
	last = get_last_token(data->tokens[i]);
	if (last && (last->type == IN_RED || last->type == OUT_RED
			|| last->type == APP_RED || last->type == HER_DOC))
	{
		if (last->type == HER_DOC)
			new = new_token(ft_strdup(str), DELIMETER);
		else
			new = new_token(ft_strdup(str), FILE);
	}
	else if (red == 4)
		new = new_token(ft_strdup(str), HER_DOC);
	else if (red == 3)
		new = new_token(ft_strdup(str), APP_RED);
	else if (red == 2)
		new = new_token(ft_strdup(str), OUT_RED);
	else if (red == 1)
		new = new_token(ft_strdup(str), IN_RED);
	else if (j == 0)
		new = new_token(ft_strdup(str), CMD);
	else
		new = new_token(ft_strdup(str), ARG);
	token_add_back(&(data->tokens[i]), new);
}
