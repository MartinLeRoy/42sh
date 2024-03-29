/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 14:18:25 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/24 19:43:39 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	resultat;

	resultat = 0;
	if (str == NULL)
		return (0);
	while (*str != '\0')
	{
		resultat++;
		str++;
	}
	return (resultat);
}
