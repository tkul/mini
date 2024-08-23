/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:48:55 by tkul              #+#    #+#             */
/*   Updated: 2024/08/24 01:21:52 by ayirmili         ###   ########.fr       */
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

int	ft_parser_init(t_data *data)
{
	data->i = -1;
	data->lexer = malloc(sizeof(t_lexer));
	if (!data->lexer)
		return (ERROR);
	data->lexer->key = NULL;
	data->lexer->value = NULL;
	data->pipe_count = ft_count_pipes(data, data->cmd);
	if (ft_count_pipes(data, data->cmd) == -1)
		return (free(data->lexer), ERROR);
	if (ft_control_quotes(data->cmd) == ERROR)
		return (free(data->lexer), ERROR);
	if (ft_init_redirections(data) == ERROR)
		return (free(data->lexer), ERROR);
	data->cmds = ft_split_by_quote(data->cmd, '|');
	if (!data->cmds)
		return (free(data->lexer), ERROR);
	return (SUCCESS);
}

int	ft_parser_free(t_data *data)
{
	ft_free_array(data->cmds);
	if (data->lexer->value)
		free(data->lexer->value);
	if (data->lexer->key)
		free(data->lexer->key);
	if (ft_control_token(data, data->tokens) == ERROR)
		return (free(data->lexer), ERROR);
	free(data->lexer);
	return (SUCCESS);
}

int	ft_parser(t_data *data)
{
	if (ft_parser_init(data) == ERROR)
		return (ERROR);
	while (data->cmds[++data->i])
	{
		data->new = ft_split_by_quote(data->cmds[data->i], ' ');
		if (!data->new)
			return (free(data->lexer), ERROR);
		data->j = -1;
		while (data->new[++data->j])
		{
			if (ft_remove_quotes(data, &(data->new[data->j])) == ERROR)
				return (free(data->lexer), ERROR);
			if (ft_create_token(data, data->new[data->j], data->i,
					data->j) == ERROR)
				return (free(data->lexer), ERROR);
		}
		ft_free_array(data->new);
	}
	ft_redirect_arrange(data->tokens);
	if (ft_parser_free(data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
