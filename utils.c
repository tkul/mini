/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:49:45 by tkul              #+#    #+#             */
/*   Updated: 2024/08/21 11:01:31 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
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

int	my_isalpha(int c)
{
	if (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
