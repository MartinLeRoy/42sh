/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/18 19:58:53 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/25 16:49:41 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "libft.h"

static char			*st_get_word_indir(char *word, int start, t_lst_star *list)
{
	int		end;
	char	*word_indir;

	end = start;
	while (word[start] && word[start] != '/')
		start--;
	while (word[end] && word[end] != '/')
		end++;
	word_indir = ft_strsub(word, (start + 1), (end - (start + 1)));
	if (word[end])
		list->after_word = ft_strdup(&word[end]);
	else
		list->after_word = NULL;
	return (word_indir);
}

static char			*st_get_dir(char *str, int pos, t_lst_star *list)
{
	char		*dir;

	while (pos && str[pos] && str[pos - 1] != '/')
		pos--;
	if (pos == 0)
	{
		dir = ft_strnew(1);
		dir[0] = '.';
		list->dir_flag = 0;
	}
	else
	{
		dir = ft_strsub(str, 0, pos);
		list->dir_flag = 1;
		list->word_in_dir = st_get_word_indir(str, pos, list);
	}
	return (dir);
}

static char			*st_get_word(char *cmd, int start)
{
	char	*word;
	int		end;

	end = start;
	while (start != 0 && cmd[start] && !ft_isspace(cmd[start - 1]))
		start--;
	while (cmd[end] && !ft_isspace(cmd[end]))
		end++;
	word = ft_strsub(cmd, start, end - start);
	return (word);
}

t_lst_star			*init_lst_star(char *cmd, int pos)
{
	t_lst_star	*new;

	if ((new = (t_lst_star *)malloc(sizeof(*new))) == NULL)
		ft_exit(PROG, 1);
	new->first = NULL;
	new->last = NULL;
	new->word_in_dir = NULL;
	new->pos_str = pos;
	new->word = st_get_word(cmd, pos);
	new->pos_inword = st_get_posinword(new->word);
	new->dir = st_get_dir(new->word, new->pos_inword, new);
	new->start = st_get_start(cmd, pos);
	new->end = st_get_end(cmd, pos);
	return (new);
}
