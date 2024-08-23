/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:48:55 by tkul              #+#    #+#             */
/*   Updated: 2024/08/23 19:14:33 by tkul             ###   ########.fr       */
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
	data->lexer->pipe_count = ft_count_pipes(data, data->cmd);
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

static void ft_remove_quotes(t_data *data)
{
	int		i;
	int		quote;
	int		rm1;
	int		rm2;
	char	*s;
	t_token	*tmp;
	int		j;

	i = 0;
	j = 0;
	quote = 0;
	rm1 = -1;
	rm2 = -1;
	while (data->tokens[j])
	{
		tmp = data->tokens[j];
		while (tmp)
		{
			s = ft_strdup(tmp->value);
			i = 0;
			rm1 = -1;
			rm2 = -1;
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
				if (!s)
					break ;
			}
			free(tmp->value);
			tmp->value = s;
			tmp = tmp->next;
		}
		j++;
	}
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
			if (ft_set_env_varibles(data, &(data->new[data->j])) == ERROR)
				return (free(data->lexer), ERROR);
			if (ft_create_token(data, data->new[data->j], data->i,
					data->j) == ERROR)
				return (free(data->lexer), ERROR);
		}
		ft_free_array(data->new);
	}
	ft_remove_quotes(data);
	ft_redirect_arrange(data->tokens);
	if (ft_parser_free(data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
