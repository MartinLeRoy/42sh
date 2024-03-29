/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 15:33:22 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/25 20:29:35 by dcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putnbr(int nb)
{
	char	c;

	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
	}
	if ((nb / 10) == 0)
	{
		c = nb + '0';
		write(1, &c, 1);
		return ;
	}
	ft_putnbr(nb / 10);
	c = nb % 10 + '0';
	write(1, &c, 1);
}
