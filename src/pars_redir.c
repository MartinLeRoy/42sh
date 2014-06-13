/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 19:58:21 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/21 17:59:45 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parseur.h"
#include "lexer.h"
#include "libft.h"

static t_inst	*redir_in_last_inst(t_lexer *node, t_parse *tree, char **tab)
{
	t_inst		*last_inst;

	last_inst = find_last_inst(tree);
	add_redir(last_inst, *tab, node->type);
	return (last_inst);
}

t_lexer			*add_redir_tree(t_lexer *node, t_parse *tree)
{
	char		**tab;
	t_inst		*ret;

	tab = NULL;
	if (node->next)
	{
		if (node->next->type == CMD)
			tab = ft_strsplitspace(node->next->str);
		else if (node->next->type > 0 && node->next->type < 4)
			tab = ft_strsplit(node->next->str, '\0');
	}
	if (node->prev == NULL || (node->prev->type > 3 && node->prev->type < 8))
		ret = redir_in_new_inst(node, tree, tab);
	else
		ret = redir_in_last_inst(node, tree, tab);
	cat_cmd_pars(ret, tab, 1);
	ft_tabfree(&tab);
	return (node->next->next);
}

int				check_redir(t_lexer *node)
{
	if (node->type > 7 && node->type < 13 && node->next
		&& node->next->type >= 0 && node->next->type < 4)
		return (1);
	return (0);
}
