/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 00:52:19 by tkul              #+#    #+#             */
/*   Updated: 2023/10/18 00:02:21 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;
	char		c;

	if (fd < 0)
		return ;
	nb = n;
	if (nb < 0)
	{
		nb *= -1;
		if (!write (fd, "-", 1))
			return ;
	}
	if (nb < 10)
	{
		c = nb + '0';
		if (!write(fd, &c, 1))
			return ;
	}
	else
	{
		ft_putnbr_fd(nb / 10, fd);
		c = nb % 10 + '0';
		if (!write(fd, &c, 1))
			return ;
	}
}
