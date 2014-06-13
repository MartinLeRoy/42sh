/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbslashed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 14:20:30 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/25 16:01:48 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			ft_isbslashed(char *str, int pos)
{
	int		flag;

	flag = 0;
	if (pos == 0)
		return (0);
	while ((pos - 1) >= 0 && str[pos - 1] == '\\')
	{
		if (str[pos - 1] == '\\')
		{
			flag++;
		}
		pos--;
	}
	if (flag == 0)
		return (0);
	else if ((flag % 2) == 0)
		return (0);
	else
		return (1);
	return (0);
}
