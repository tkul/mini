/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:49:39 by tkul              #+#    #+#             */
/*   Updated: 2024/09/03 13:20:15 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_helper(t_data *data, int i, char **new, t_token *tmp)
{
	char	*tmp_value;
	t_token	*ntoken;

	while (tmp)
	{
		if (tmp->index < 0)
		{
			ntoken = new_token(ft_strdup(tmp->value), tmp->type, tmp->index);
			token_add_back(&(data->tokens[i]), ntoken);
			tmp = tmp->next;
			continue ;
		}
		tmp_value = *new;
		*new = ft_joinstr_index(*new, tmp->value, tmp->index + data->offset);
		free(tmp_value);
		data->offset += ft_strlen(tmp->value);
		tmp = tmp->next;
	}
}

void	ft_apply_token_buffer(t_data *data, int i, int is_created_token_is_null)
{
	t_token	*tmp;
	t_token	*last;
	char	*new;

	tmp = data->token_buffer;
	data->offset = 0;
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
	ft_helper(data, i, &new, tmp);
	ft_tokenclear(&data->token_buffer, free);
	data->token_buffer = NULL;
	free(last->value);
	last->value = new;
}

int	ft_find_type(t_data *data, char *str, int j)
{
	if (data->last && (data->last->type == IN_RED || data->last->type == OUT_RED
			|| data->last->type == APP_RED || data->last->type == HER_DOC))
	{
		if (data->red > 0 && data->red < 5)
			return (ft_error(data, SYNTAX_ERROR), ERROR);
		if (data->last->type == HER_DOC)
			data->new_token = new_token(ft_strdup(str), DELIMETER, -1);
		else
			data->new_token = new_token(ft_strdup(str), FILE, -1);
	}
	else if (data->red == 4 && data->red_extra == 4)
		data->new_token = new_token(ft_strdup(str), HER_DOC, -1);
	else if (data->red == 3 && data->red_extra == 3)
		data->new_token = new_token(ft_strdup(str), APP_RED, -1);
	else if (data->red == 2 && data->red_extra == 2)
		data->new_token = new_token(ft_strdup(str), OUT_RED, -1);
	else if (data->red == 1 && data->red_extra == 1)
		data->new_token = new_token(ft_strdup(str), IN_RED, -1);
	else if (j == 0)
		data->new_token = new_token(ft_strdup(str), CMD, -1);
	else
		data->new_token = new_token(ft_strdup(str), ARG, -1);
	return (SUCCESS);
}

int	ft_helper_create_token(t_data *data, char *str, int i, int j)
{
	char	*tmp;

	if (str && *str)
	{
		data->is_created_token_is_null = 0;
		if (data->tokens)
			data->last = get_last_token(data->tokens[i]);
		if (ft_find_type(data, str, j) == ERROR)
			return (ERROR);
		token_add_back(&(data->tokens[i]), data->new_token);
	}
	else if (ft_toknssize(data->token_buffer) == 0 && data->is_really_env == 0)
	{
		tmp = ft_strdup("a");
		tmp[0] = 1;
		token_add_back(&(data->tokens[i]), new_token(tmp, CMD, -1));
	}
	return (SUCCESS);
}

int	ft_create_token(t_data *data, char *str, int i, int j)
{
	data->is_created_token_is_null = 1;
	data->red_extra = is_redirection(data->original[j]);
	data->red = is_redirection(str);
	if (ft_helper_create_token(data, str, i, j) == ERROR)
		return (ERROR);
	ft_apply_token_buffer(data, i, data->is_created_token_is_null);
	return (SUCCESS);
}
