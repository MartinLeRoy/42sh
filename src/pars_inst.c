/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_inst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 20:36:53 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/26 16:35:49 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parseur.h"
#include "libft.h"

void			add_inst_inor(t_lexer *node, t_parse *tree)
{
	t_job		*last_job;

	last_job = find_last_job(tree);
	if (!is_job_free(last_job))
	{
		last_job->next = init_job();
		last_job->next->prev = last_job;
		last_job = last_job->next;
	}
	last_job->or_inst = init_inst(node->str);
}

void			add_inst_inand(t_lexer *node, t_parse *tree)
{
	t_job		*last_job;

	last_job = find_last_job(tree);
	if (!is_job_free(last_job))
	{
		last_job->next = init_job();
		last_job->next->prev = last_job;
		last_job = last_job->next;
	}
	last_job->and_inst = init_inst(node->str);
}

void			cat_inst_toprev(t_lexer *node, t_parse *tree)
{
	t_inst		*last_inst;
	char		**tab;

	tab = ft_strsplitspace(node->str);
	last_inst = find_last_inst(tree);
	if (is_inst_free(last_inst))
		last_inst->arg = tab;
	else
	{
		cat_cmd_pars(last_inst, tab, 0);
		ft_tabfree(&tab);
	}
}

t_lexer			*add_inst(t_lexer *node, t_parse *tree)
{
	t_job		*last_job;
	t_inst		*last_inst;

	if (node->prev == NULL || node->prev->type == SEP)
	{
		if (node->prev == NULL)
			add_cmd_tree(tree);
		last_job = find_last_job(tree);
		last_job->inst = init_inst(node->str);
	}
	else if (node->prev->type == PIPE)
	{
		last_inst = find_last_inst(tree);
		last_inst->next = init_inst(node->str);
		last_inst->next->prev = last_inst;
	}
	else if (node->prev->type == OR)
		add_inst_inor(node, tree);
	else if (node->prev->type == AND)
		add_inst_inand(node, tree);
	else if (node->prev->type >= 0 && node->prev->type < 4)
		cat_inst_toprev(node, tree);
	return (node->next);
}

int				check_inst(t_lexer *node)
{
	if (node->type == CMD)
		return (1);
	return (0);
}
