/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_star_step.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/18 19:52:25 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/26 16:26:01 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"

static void			st_free_lst(t_lst_star *starz)
{
	if (starz->word)
		free(starz->word);
	if (starz->dir)
		free(starz->dir);
	if (starz->word_in_dir)
		free(starz->word_in_dir);
}

static void			free_star_list(t_lst_star *starz)
{
	t_star		*tmp;
	t_star		*keep;

	tmp = starz->first;
	while (tmp)
	{
		if (tmp->add)
			free(tmp->add);
		keep = tmp;
		tmp = tmp->next;
		free(keep);
	}
	st_free_lst(starz);
	free(starz);
}

static void			star_in_lx(t_lexer *node, char **env)
{
	char			*str;
	int				i;
	t_lst_star		*star_list;

	i = 0;
	str = node->str;
	while (str[i])
	{
		if (str[i] == '*' && !ft_isbslashed(str, i))
		{
			star_list = get_star(str, i);
			add_star(star_list, node, env);
			if (star_list->first)
			{
				str = node->str;
				i = -1;
			}
			free_star_list(star_list);
		}
		i++;
	}
}

void				check_star_inlex(t_lx *lex, char **env)
{
	t_lexer			*browse_lx;

	if (lex == NULL)
		return ;
	browse_lx = lex->first;
	while (browse_lx)
	{
		if (browse_lx->type == CMD)
			star_in_lx(browse_lx, env);
		browse_lx = browse_lx->next;
	}
}
