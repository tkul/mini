/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:49:39 by tkul              #+#    #+#             */
/*   Updated: 2024/08/20 23:12:09 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirect_arrange(t_token **tokens)
{
	t_token	**tmp1;
	t_token	*tmp2;
	int		i;

	i = -1;
	tmp1 = tokens;
	while (tmp1[++i])
	{
		tmp2 = tmp1[i];
		while (tmp2)
		{
			if (tmp2->type == CMD)
				break ;
			if (is_redirection(tmp2->value) && tmp2->next && tmp2->next->next
				&& is_redirection(tmp2->next->next->value))
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

void	ft_apply_token_buffer(t_data *data, int i, int is_created_token_is_null)
{
	t_token	*tmp;
	t_token	*last;
	t_token	*ntoken;
	int		offset;
	char	*new;

	tmp = data->token_buffer;
	offset = 0;
	if (!tmp)
		return ;
	last = get_last_token(data->tokens[i]);
	if (is_created_token_is_null)
	{
		if (!last)
			token_add_back(&(data->tokens[i]), new_token(ft_strdup(""), CMD,
					-1));
		else
			token_add_back(&(data->tokens[i]), new_token(ft_strdup(""), ARG,
					-1));
		last = get_last_token(data->tokens[i]);
	}
	new = ft_strdup(last->value);
	while (tmp)
	{
		if (tmp->index < 0)
		{
			ntoken = new_token(ft_strdup(tmp->value), tmp->type, tmp->index);
			token_add_back(&(data->tokens[i]), ntoken);
			tmp = tmp->next;
			continue ;
		}
		new = ft_joinstr_index(new, tmp->value, tmp->index + offset);
		offset += ft_strlen(tmp->value);
		tmp = tmp->next;
	}
	ft_tokenclear(&data->token_buffer, free);
	data->token_buffer = NULL;
	free(last->value);
	last->value = new;
}

int	ft_create_token(t_data *data, char *str, int i, int j)
{
	t_token	*new;
	t_token	*last;
	int		red;
	int		is_created_token_is_null;

	is_created_token_is_null = 1;
	last = NULL;
	red = is_redirection(str);
	if (str && *str)
	{
		is_created_token_is_null = 0;
		if (data->tokens)
			last = get_last_token(data->tokens[i]);
		if (last && (last->type == IN_RED || last->type == OUT_RED
				|| last->type == APP_RED || last->type == HER_DOC))
		{
			if (red > 0 && red < 5)
				return (ft_error(data, SYNTAX_ERROR), ERROR);
			if (last->type == HER_DOC)
				new = new_token(ft_strdup(str), DELIMETER, -1);
			else
				new = new_token(ft_strdup(str), FILE, -1);
		}
		else if (red == 4)
			new = new_token(ft_strdup(str), HER_DOC, -1);
		else if (red == 3)
			new = new_token(ft_strdup(str), APP_RED, -1);
		else if (red == 2)
			new = new_token(ft_strdup(str), OUT_RED, -1);
		else if (red == 1)
			new = new_token(ft_strdup(str), IN_RED, -1);
		else if (j == 0)
			new = new_token(ft_strdup(str), CMD, -1);
		else
			new = new_token(ft_strdup(str), ARG, -1);
		token_add_back(&(data->tokens[i]), new);
	}
	ft_print_token_buffer(data->token_buffer);
	ft_apply_token_buffer(data, i, is_created_token_is_null);
	return (SUCCESS);
}
