/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/22 16:38:03 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/27 20:41:24 by dcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "termcaps.h"
#include "libft.h"

int				sh_exit(char **req, char ***env)
{
	int		val;

	(void)env;
	val = 0;
	if (req[1] && req[2] && req[2] != '\0')
	{
		write(2, "exit: too many arguments\n", 25);
		return (-1);
	}
	val = ft_atoi(req[1]);
	restore_env(1);
	write(1, "exit\n", 5);
	exit(val);
	return (0);
}
