/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:00:46 by tkul              #+#    #+#             */
/*   Updated: 2024/09/05 03:10:35 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_heredoc_key(char *s)
{
	int		j;
	int		i;
	char	*key;

	i = 0;
	j = 0;
	while (s[i] && ft_isalphaaa(s[i]) == 1)
		i++;
	key = (char *)malloc(i + 1);
	i = 0;
	while (s[i] && ft_isalphaaa(s[i]) == 1)
	{
		key[j] = s[i];
		i++;
		j++;
	}
	key[j] = '\0';
	return (key);
}

void	ft_heredoc_writer(t_data *data, int pipe_fd[2], char **buff)
{
	int		i;
	char	*tmp_buff;
	char	*key;
	char	*value;
	char	*status;

	i = 0;
	key = NULL;
	value = NULL;
	tmp_buff = NULL;
	status = NULL;
	if (ft_strchr(*buff, '$'))
	{
		while ((*buff)[i])
		{
			if ((*buff)[i] == '$' && (*buff)[i + 1] == '?')
			{
				tmp_buff = remove_by_index(*buff, i, 1);
				free(*buff);
				status = ft_itoa(data->status);
				*buff = ft_joinstr_index(tmp_buff, status, i);
				free(status);
				free(tmp_buff);
			}
			else if ((*buff)[i] == '$' && ft_isalphaaa((*buff)[i + 1]))
			{
				key = get_heredoc_key(&((*buff)[i + 1]));
				value = ft_getenv_by_key(key, data->env);
				if (!value)
					value = ft_strdup("");
				tmp_buff = remove_by_index(*buff, i, ft_strlen(key));
				free(*buff);
				*buff = ft_joinstr_index(tmp_buff, value, i);
				free(tmp_buff);
				if (value)
					free(value);
				if (key)
					free(key);
			}
			i++;
		}
	}
	write(pipe_fd[1], *buff, ft_strlen(*buff));
	write(pipe_fd[1], "\n", 1);
}

int	ft_heredoc_helper(t_token *token, t_exec *exec, char *buff)
{
	if (exec->count_heredocs > 1)
	{
		if (!ft_strcmp(buff, exec->is_here_doc))
		{
			free(buff);
			while (token)
			{
				if (!ft_strcmp(token->value, exec->is_here_doc))
					break ;
				token = token->next;
			}
			exec->is_here_doc = ft_is_here_doc2(exec, token);
			exec->count_heredocs--;
			return (1);
		}
	}
	return (0);
}

void	ft_heredoc_loop(t_data *data, t_token *token, t_exec *exec,
		int pipe_fd[2])
{
	int		i;
	char	*buff;

	i = 0;
	buff = "init_value";
	while (buff && exec->count_heredocs > 0)
	{
		buff = readline("> ");
		if (ft_heredoc_helper(token, exec, buff))
			continue ;
		if (buff == NULL || !ft_strcmp(buff, exec->is_here_doc))
		{
			if (buff == NULL || i == exec->count_heredocs - 1)
			{
				if (buff)
					free(buff);
				break ;
			}
			i++;
			if (buff)
				free(buff);
			continue ;
		}
		if (i == exec->count_heredocs - 1)
			ft_heredoc_writer(data, pipe_fd, &buff);
		if (buff)
			free(buff);
	}
}
