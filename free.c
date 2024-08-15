/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:28:23 by tkul              #+#    #+#             */
/*   Updated: 2024/08/14 11:09:58 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tokens(t_token **tokens)
{
	t_token	**tmp;
	t_token	*next;
	t_token	*tmp2;
	int		i;

	if (!tokens || !*tokens)
		return ;
	tmp = tokens;
	i = 0;
	while (tmp[i])
	{
		next = tmp[i];
		while (next)
		{
			tmp2 = next;
			next = next->next;
			free(tmp2->value);
			free(tmp2);
		}
		i++;
	}
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
