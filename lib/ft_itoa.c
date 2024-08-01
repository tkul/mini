/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tugcekul <tugcekul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:18:37 by tkul              #+#    #+#             */
/*   Updated: 2024/07/31 23:23:32 by tugcekul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digit_and_is_negative(long n)
{
	int		count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
	{
		count++;
		n = n * -1;
	}
	while (n / 10 != 0)
	{
		count++;
		n = n / 10;
	}
	count++;
	return (count);
}

static void	ft_make(char *str, size_t nb, int *level)
{
	if (nb > 9)
	{
		ft_make(str, nb / 10, level);
		ft_make(str, nb % 10, level);
	}
	else
	{
		str[*level] = nb + '0';
		(*level)++;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		level;
	long	nb;

	nb = n;
	str = (char *)malloc(sizeof(char) * (count_digit_and_is_negative(nb) + 1));
	if (!str)
		return (NULL);
	level = 0;
	if (n < 0)
	{
		str[0] = '-';
		nb = nb * -1;
		level++;
	}
	ft_make(str, (size_t)nb, &level);
	str[level] = '\0';
	return (str);
}
