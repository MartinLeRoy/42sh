/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaf <jchenaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 07:38:13 by jchenaf           #+#    #+#             */
/*   Updated: 2014/03/27 17:30:57 by dcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include "termcaps.h"
#include "libft.h"

static t_file		*init_node(char *tmp)
{
	t_file	*new;

	if ((new = (t_file *)malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->str = ft_strtrim(tmp);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void				add_to_list(t_auto *autocomp, char *tmp)
{
	t_file	*node;

	node = init_node(tmp);
	if (autocomp->first == NULL)
	{
		autocomp->first = node;
		autocomp->last = node;
	}
	else
	{
		autocomp->last->next = node;
		node->prev = autocomp->last;
		autocomp->last = node;
	}
}

int					find_cmd(t_auto	*file, int token, int i)
{
	DIR				*dir;
	struct dirent	*diren;

	if (file->path[0] == NULL)
		return (1);
	while (file->path[i])
	{
		if ((dir = opendir(file->path[i])) == NULL)
			return (1);
		while ((diren = readdir(dir)) != NULL)
		{
			if (token == 0)
				add_to_list(file, diren->d_name);
			else
			{
				if (auto_comp_check5(file->end, diren->d_name) == 1
					&& diren->d_name[0] != '.')
					add_to_list(file, diren->d_name);
			}
		}
		closedir(dir);
		i++;
	}
	return (i);
}
