/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:48:55 by tkul              #+#    #+#             */
/*   Updated: 2024/08/10 15:41:54 by tkul             ###   ########.fr       */
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

static void	init_split(t_split **s, const char *str, char c)
{
	*s = malloc(sizeof(t_split));
	if (!*s)
		return ;
	(*s)->i = 0;
	(*s)->j = 0;
	(*s)->k = 0;
	(*s)->quote = -1;
	(*s)->cmds = malloc(sizeof(char *) * (count_word(str, c) + 1));
	if (!(*s)->cmds)
		return ;
}

char	**ft_split_by_quote(const char *str, char c)
{
	t_split	*s;
	char	**tmp;

	init_split(&s, str, c);
	if (!s)
		return (NULL);
	while (str[s->i])
	{
		s->k = s->i;
		while (str[s->i] && (s->quote != -1 || str[s->i] != c))
		{
			ft_set_quote_type(&s->quote, str[s->i]);
			s->i++;
		}
		if (s->i > s->k)
		{
			s->cmds[s->j] = ft_substr(str, s->k, s->i - s->k);
			if (!s->cmds[s->j])
				return (NULL);
			s->j++;
		}
		if (str[s->i] != '\0')
			s->i++;
	}
	s->cmds[s->j] = NULL;
	tmp = s->cmds;
	free(s);
	return (tmp);
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	ft_lexer(t_data *data)
{
	char	**cmds;
	char	**new;
	int		i;
	int		j;

	i = -1;
	data->lexer = malloc(sizeof(t_lexer));
	if (!data->lexer)
		return (-1);
	data->lexer->pipe_count = ft_count_pipes(data->cmd);
	if (data->lexer->pipe_count == -1)
		return (free(data->lexer), -1);
	if (ft_control_quotes(data->cmd) == -1)
		return (-1);
	if (ft_init_redirections(data) == -1)
		return (-1);
	cmds = ft_split_by_quote(data->cmd, '|');
	if (!cmds)
		return (free(data->lexer), -1);
	while (cmds[++i])
	{
		new = ft_split_by_quote(cmds[i], ' ');
		if (!new)
			return (free(data->lexer), -1);
		j = -1;
		while (new[++j])
		{
			if (handle_dollar(data, &(new[j])) == -1)
				return (-1);
			if (ft_remove_quotes(&(new[j])) == -1)
				return (-1);
			ft_create_token(data, new[j], i, j);
		}
		ft_free_array(new);
	}
	ft_free_array(cmds);
	return (0);
}
