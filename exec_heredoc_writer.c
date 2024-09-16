/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_writer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:34:24 by tkul              #+#    #+#             */
/*   Updated: 2024/09/05 12:07:31 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_heredoc_key(char *s)
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

static void	ft_writer_helper(t_data *data, char **buff, int i)
{
	char	*tmp_buff;
	char	*status;

	status = NULL;
	tmp_buff = remove_by_index(*buff, i, 1);
	free(*buff);
	status = ft_itoa(data->status);
	*buff = ft_joinstr_index(tmp_buff, status, i);
	free(status);
	free(tmp_buff);
}

static void	ft_writer_helper2(t_data *data, char **buff, int i)
{
	char	*tmp_buff;
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
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

void	ft_heredoc_writer(t_data *data, int pipe_fd[2], char **buff)
{
	int	i;

	i = 0;
	if (ft_strchr(*buff, '$'))
	{
		while ((*buff)[i])
		{
			if ((*buff)[i] == '$' && (*buff)[i + 1] == '?')
				ft_writer_helper(data, buff, i);
			else if ((*buff)[i] == '$' && ft_isalphaaa((*buff)[i + 1]))
				ft_writer_helper2(data, buff, i);
			i++;
		}
	}
	write(pipe_fd[1], *buff, ft_strlen(*buff));
	write(pipe_fd[1], "\n", 1);
}
