/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thisfilewilldeleted.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:44:54 by tkul              #+#    #+#             */
/*   Updated: 2024/08/09 21:46:25 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_tokens(t_token **token)
{
	t_token	**tmp;
	t_token	*next;
	int		i;

	if (!token || !*token)
		return ;
	tmp = token;
	i = 0;
	while (tmp[i])
	{
		next = tmp[i];
		while (next)
		{
			printf("Token %d: type:%d, %s$\n", i, next->type, next->value);
			next = next->next;
		}
		i++;
	}
}
