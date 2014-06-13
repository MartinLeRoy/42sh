/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 20:48:16 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/22 17:45:46 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parseur.h"
#include "lexer.h"

t_lexer				*add_quote(t_lexer *node, t_parse *tree)
{
	t_job		*last_job;
	t_inst		*last_inst;
	char		**tab;

	tab = ft_strsplit(node->str, '\0');
	if (node->prev == NULL || node->prev->type == SEP)
	{
		if (node->prev == NULL)
			add_cmd_tree(tree);
		last_job = find_last_job(tree);
		last_job->inst = init_inst(NULL);
		last_job->inst->arg = tab;
	}
	else if (node->prev->type >= 0 && node->prev->type < 4)
	{
		last_inst = find_last_inst(tree);
		if (is_inst_free(last_inst))
			last_inst->arg = tab;
		else
		{
			cat_cmd_pars(last_inst, tab, 0);
			ft_tabfree(&tab);
		}
	}
	return (node->next);
}

int					check_quote(t_lexer *node)
{
	if (node->type > 0 && node->type < 4)
		return (1);
	return (0);
}
