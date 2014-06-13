/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaf <jchenaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 07:37:41 by jchenaf           #+#    #+#             */
/*   Updated: 2014/03/27 18:18:20 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"
#include "libft.h"
#include <stdlib.h>

static int		ft_tablen_auto(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

static char		*auto_get_end_word(char *str)
{
	char		*tmp;
	int			i;

	i = 0;
	while (str[i])
		i++;
	i--;
	while (i >= 0)
	{
		if (str[i] == '/' || str[i] == ' ')
			break ;
		i--;
	}
	i++;
	tmp = ft_strsub(str, i, ft_strlen(str) - i);
	return (tmp);
}

static char		*auto_get_start(char *str)
{
	char		*tmp;
	int			i;

	i = 0;
	while (str[i])
		i++;
	if (ft_strchr(str, '/') != NULL)
	{
		while (str[i] != '/')
			i--;
	}
	tmp = ft_strsub(str, 0, i + 1);
	return (tmp);
}

void			ft_auto_init_data(char *cmd, t_auto *aut)
{
	aut->tab = ft_strsplitspace(cmd);
	aut->len = ft_tablen_auto(aut->tab);
	aut->start = auto_get_start(aut->tab[aut->len - 1]);
	aut->end = auto_get_end_word(aut->tab[aut->len - 1]);
}
