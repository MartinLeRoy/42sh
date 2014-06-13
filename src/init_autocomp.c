/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_autocomp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 20:55:39 by rabid-on          #+#    #+#             */
/*   Updated: 2014/03/26 20:58:57 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "termcaps.h"

t_auto	*ft_auto_init(void)
{
	t_auto		*new;

	if ((new = (t_auto *)malloc(sizeof(*new))) == NULL)
		ft_exit("malloc", 1);
	new->first = NULL;
	new->last = NULL;
	new->len = 0;
	new->tab = NULL;
	new->start = NULL;
	new->end = NULL;
	new->path = NULL;
	return (new);
}

void	free_list_auto(t_auto *file)
{
	t_file		*tmp;
	t_file		*keep;

	if (file == NULL)
		return ;
	tmp = file->first;
	while (tmp)
	{
		keep = tmp->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
		tmp = keep;
	}
	if (file->path)
		ft_tabfree(&file->path);
	if (file->tab)
		ft_tabfree(&file->tab);
	if (file->end)
		free(file->end);
	if (file->start)
		free(file->start);
	free(file);
}
