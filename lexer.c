/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:48:55 by tkul              #+#    #+#             */
/*   Updated: 2024/08/15 18:37:55 by tkul             ###   ########.fr       */
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
	data->lexer->pipe_count = ft_count_pipes(data, data->cmd);
	if (data->lexer->pipe_count == ERROR)
		return (free(data->lexer), -1);
	if (ft_control_quotes(data->cmd) == ERROR)
		return (ERROR);
	if (ft_init_redirections(data) == ERROR)
		return (ERROR);
	cmds = ft_split_by_quote(data->cmd, '|');
	if (!cmds)
		return (free(data->lexer), ERROR);
	if (handle_dollar(data, cmds) == ERROR)
		return (ERROR);
	while (cmds[++i])
	{
		new = ft_split_by_quote(cmds[i], ' ');
		if (!new)
			return (free(data->lexer), ERROR);
		j = -1;
		while (new[++j])
		{
			if (ft_remove_quotes(&(new[j])) == ERROR)
				return (ERROR);
			if (ft_create_token(data, new[j], i, j) == ERROR)
				return (ERROR);
		}
		ft_free_array(new);
	}
	ft_redirect_arrange(data->tokens);
	ft_free_array(cmds);
	if (ft_control_token(data, data->tokens) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
