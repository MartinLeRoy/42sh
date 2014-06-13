/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 20:56:21 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/22 17:37:31 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lexer.h"
#include "parseur.h"

static t_lexer		*add_pipe_ncmd(t_lexer *node, t_parse *tree)
{
	char		**tab;
	t_inst		*last_inst;

	if (node->next->type == CMD)
		tab = ft_strsplitspace(node->next->str);
	else
		tab = ft_strsplit(node->next->str, '\0');
	last_inst = find_last_inst(tree);
	last_inst->next = init_inst(NULL);
	last_inst->next->prev = last_inst;
	last_inst->next->arg = tab;
	return (node->next->next);
}

static t_lexer		*add_pipe_alone(t_lexer *node, t_parse *tree)
{
	t_inst		*last_inst;

	last_inst = find_last_inst(tree);
	last_inst->next = init_inst(NULL);
	last_inst->next->prev = last_inst;
	return (node->next);
}

t_lexer				*add_pipe(t_lexer *node, t_parse *tree)
{
	t_lexer		*ret;

	if (node->next && (node->next->type >= 0 && node->next->type < 4))
		ret = add_pipe_ncmd(node, tree);
	else
		ret = add_pipe_alone(node, tree);
	return (ret);
}

int					check_pipe(t_lexer *node)
{
	if (node->type == PIPE)
		return (1);
	return (0);
}
