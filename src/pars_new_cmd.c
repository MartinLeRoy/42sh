/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_new_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 20:59:15 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/22 17:46:05 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "parseur.h"

void			add_cmd_tree(t_parse *tree)
{
	t_cmd	*browse;

	if (tree->cmd == NULL)
		tree->cmd = init_cmd();
	else
	{
		browse = tree->cmd;
		while (browse->next)
			browse = browse->next;
		browse->next = init_cmd();
	}
}

t_lexer			*add_new_cmd(t_lexer *node, t_parse *tree)
{
	add_cmd_tree(tree);
	return (node->next);
}

int				check_new_cmd(t_lexer *node)
{
	if (node->type == SEP && node->next)
		return (1);
	return (0);
}
