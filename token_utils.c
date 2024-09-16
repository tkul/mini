/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 02:01:36 by tkul              #+#    #+#             */
/*   Updated: 2024/09/05 16:54:52 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirect_arrange(t_data *data, t_token **tokens)
{
	t_token	**tmp1;
	t_token	*tmp2;
	int		i;

	i = -1;
	data->cmd_flag = 0;
	tmp1 = tokens;
	while (tmp1[++i])
	{
		tmp2 = tmp1[i];
		while (tmp2)
		{
			if (tmp2->type == CMD)
				break ;
			if (ft_is_redirection_single(tmp2) && tmp2->next && tmp2->next->next
				&& !ft_is_redirection_single(tmp2->next->next))
				tmp2->next->next->type = CMD;
			tmp2 = tmp2->next;
		}
	}
}

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

t_token	*new_token(char *value, int type, int index)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->type = type;
	new->index = index;
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

void	ft_tokenclear(t_token **token, void (*del)(void *))
{
	t_token	*tmp;

	if (!token || !*token)
		return ;
	while (*token)
	{
		tmp = (*token)->next;
		if (del)
			del((*token)->value);
		free(*token);
		*token = tmp;
	}
	*token = NULL;
}
