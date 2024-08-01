/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:40:32 by tkul              #+#    #+#             */
/*   Updated: 2023/10/18 12:55:19 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	len;
	char			*str;

	if (!s)
		return (NULL);
	i = 0;
	len = (unsigned int)ft_strlen(s);
	str = (char *)malloc(sizeof(char) * ((int)len + 1));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = f(i, s[(int)i]);
		i++;
	}
	str[i] = '\0';
	return ((char *)str);
}
