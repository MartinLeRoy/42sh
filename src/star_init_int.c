/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_init_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/18 20:04:16 by mle-roy           #+#    #+#             */
/*   Updated: 2014/02/18 20:05:41 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

int				st_get_start(char *str, int star)
{
	while (star && str[star] && !ft_isspace(str[star - 1]))
		star--;
	return (star);
}

int				st_get_end(char *str, int star)
{
	while (str[star] && !ft_isspace(str[star]))
		star++;
	return (star);
}

int				st_get_posinword(char *word)
{
	int		ret;

	ret = 0;
	while (word[ret])
	{
		if (word[ret] == '*')
			return (ret);
		ret++;
	}
	return (0);
}
