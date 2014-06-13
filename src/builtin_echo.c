/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 20:22:08 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/27 20:41:18 by dcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int		sh_echo(char **req, char ***env)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	(void)env;
	if ((req[1] != NULL) && !(ft_strcmp(req[1], "-n")))
	{
		n++;
		i++;
	}
	while (req[++i])
	{
		if (!(((i == 2) && (n == 1)) || ((i == 1) && (n == 0))))
			write(1, " ", 1);
		ft_putstr(req[i]);
	}
	if (!n)
		write(1, "\n", 1);
	return (0);
}
