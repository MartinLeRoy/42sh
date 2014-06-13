/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_make_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/18 19:56:38 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/21 19:10:37 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include "lexer.h"
#include "libft.h"

static int			st_match_star(char *name, char *word)
{
	if (*name == *word && !*name)
		return (1);
	if (*name == *word && *name != '*')
		return (st_match_star(name + 1, word + 1));
	if (*word == '*' && *name)
		return (st_match_star(name + 1, word) + st_match_star(name, word + 1));
	if (*word == '*')
		return (st_match_star(name, word + 1));
	return (0);
}

static void			st_add_to_lst(t_lst_star *starz, char *str)
{
	t_star		*new;

	if ((new = (t_star *)malloc(sizeof(*new))) == NULL)
		ft_exit(PROG, 1);
	new->add = ft_strdup(str);
	new->next = NULL;
	new->prev = NULL;
	if (starz->first == NULL)
	{
		starz->first = new;
		starz->last = new;
	}
	else
	{
		starz->last->next = new;
		new->prev = starz->last;
		starz->last = new;
	}
}

static void			st_find_star(t_lst_star *starz)
{
	DIR				*dir;
	struct dirent	*diren;
	char			*ptr;

	if ((dir = opendir(starz->dir)) == NULL)
		return ;
	if (starz->dir_flag)
		ptr = starz->word_in_dir;
	else
		ptr = starz->word;
	while ((diren = readdir(dir)) != NULL)
	{
		if ((diren->d_name)[0] != '.')
		{
			if (st_match_star(diren->d_name, ptr))
				st_add_to_lst(starz, diren->d_name);
		}
	}
	closedir(dir);
}

t_lst_star			*get_star(char *cmd, int pos)
{
	t_lst_star		*new;

	new = init_lst_star(cmd, pos);
	st_find_star(new);
	return (new);
}
