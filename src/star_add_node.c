/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_add_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/18 20:10:25 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/25 16:20:09 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "libft.h"

static int		star_len(t_star *ptr)
{
	int		len;
	int		space;
	t_star	*node;

	node = ptr;
	len = 0;
	space = 0;
	while (node)
	{
		len += ft_strlen(node->add);
		space++;
		node = node->next;
	}
	len += space;
	return (len);
}

static void		st_rep_star(t_lst_star *starz, t_lexer *node, t_star *browse)
{
	char	*new;
	int		len;
	int		i;
	int		j;

	i = -1;
	len = star_len(starz->first);
	new = ft_strnew((ft_strlen(node->str) - 1) + len);
	while (++i != starz->start)
		new[i] = (node->str)[i];
	while (browse)
	{
		j = 0;
		while ((browse->add)[j])
			new[i++] = (browse->add)[j++];
		if (browse->next)
			new[i++] = ' ';
		browse = browse->next;
	}
	while ((node->str)[starz->end])
		new[i++] = (node->str)[(starz->end)++];
	free(node->str);
	node->str = new;
}

static void		st_add_dir_tostar(t_lst_star *starz)
{
	char	*tmp;
	char	*tmp2;
	t_star	*browse;

	browse = starz->first;
	while (browse)
	{
		tmp = ft_strjoin(starz->dir, browse->add);
		if (starz->after_word)
		{
			tmp2 = ft_strjoin(tmp, starz->after_word);
			free(tmp);
			tmp = tmp2;
		}
		free(browse->add);
		browse->add = tmp;
		browse = browse->next;
	}
}

void			add_star(t_lst_star *starz, t_lexer *node, char **env)
{
	if (starz->first == NULL)
		return ;
	if (starz->dir_flag)
	{
		st_add_dir_tostar(starz);
		if (star_exist(starz, env))
			return ;
	}
	st_rep_star(starz, node, starz->first);
}
