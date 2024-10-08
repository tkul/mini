/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:48:23 by tkul              #+#    #+#             */
/*   Updated: 2024/09/04 13:39:10 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_joinstr_index_creation(char *s1, char *s2, int start_index,
		char *new)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s1[i] && i < start_index)
	{
		new[i] = s1[i];
		i++;
	}
	k = i;
	while (s2[j])
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	while (s1[k])
	{
		new[i] = s1[k];
		i++;
		k++;
	}
	new[i] = '\0';
}

char	*ft_joinstr_index(char *s1, char *s2, int start_index)
{
	char	*new;

	new = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		return (NULL);
	ft_joinstr_index_creation(s1, s2, start_index, new);
	return (new);
}

void	remove_index(char **s, int index)
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
