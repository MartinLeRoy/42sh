/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/27 17:04:13 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/25 20:30:01 by dcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strcdup(char const *s, char c)
{
	char		*ret;
	size_t		i;

	if (s == NULL)
		return (NULL);
	i = -1;
	ret = (char *)s;
	while (ret[++i] && ret[i] != c)
		;
	return (ft_strndup(ret, i));
}
