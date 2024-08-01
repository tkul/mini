/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:37:43 by tkul              #+#    #+#             */
/*   Updated: 2023/10/20 14:14:02 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*temp;
	t_list	*list;

	if (lst == NULL)
		return (NULL);
	current = lst;
	list = NULL;
	while (current)
	{
		temp = ft_lstnew(f(current->content));
		if (!temp)
		{
			ft_lstclear(&list, del);
			return (NULL);
		}
		ft_lstadd_back(&list, temp);
		current = current->next;
	}
	return (list);
}
