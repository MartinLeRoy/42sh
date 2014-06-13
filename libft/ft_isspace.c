/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 19:48:08 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/25 20:27:42 by dcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_isspace(int c)
{
	unsigned char	val;

	val = (unsigned char)c;
	if (val == '\t' || val == '\n' || val == '\v'
		|| val == '\f' || val == '\r' || val == ' ')
		return (1);
	return (0);
}
