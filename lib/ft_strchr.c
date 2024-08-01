/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:20:22 by tkul              #+#    #+#             */
/*   Updated: 2023/10/13 13:28:53 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*ptr;

	ptr = (const char *)s;
	while (*ptr)
	{
		if (*ptr == (const char)c)
			return ((char *)ptr);
		ptr++;
	}
	if (*ptr == (const char)c)
		return ((char *)ptr);
	return (NULL);
}
