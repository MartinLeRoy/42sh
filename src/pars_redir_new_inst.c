/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redir_new_inst.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 17:48:31 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/26 16:48:22 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parseur.h"

static t_inst		*add_redir_newcmd(t_lexer *node, t_parse *tree, char *name)
{
	t_cmd		*bws_cmd;

	if (node->prev == NULL)
		add_cmd_tree(tree);
	bws_cmd = tree->cmd;
	while (bws_cmd->next)
		bws_cmd = bws_cmd->next;
	bws_cmd->job = init_job();
	bws_cmd->job->inst = init_inst(NULL);
	add_redir(bws_cmd->job->inst, name, node->type);
	return (bws_cmd->job->inst);
}

static t_inst		*add_redir_inpipe(t_lexer *node, t_parse *tree, char *name)
{
	t_inst		*last_inst;

	last_inst = find_last_inst(tree);
	if (!is_inst_free(last_inst))
	{
		last_inst->next = init_inst(NULL);
		last_inst->next->prev = last_inst;
		last_inst = last_inst->next;
	}
	add_redir(last_inst, name, node->type);
	return (last_inst);
}

static t_inst		*add_redir_inor(t_lexer *node, t_parse *tree, char *name)
{
	t_job		*last_job;

	last_job = find_last_job(tree);
	if (!is_job_free(last_job))
	{
		last_job->next = init_job();
		last_job->next->prev = last_job;
		last_job = last_job->next;
	}
	last_job->or_inst = init_inst(NULL);
	add_redir(last_job->or_inst, name, node->type);
	return (last_job->or_inst);
}

static t_inst		*add_redir_inand(t_lexer *node, t_parse *tree, char *name)
{
	t_job		*last_job;

	last_job = find_last_job(tree);
	if (!is_job_free(last_job))
	{
		last_job->next = init_job();
		last_job->next->prev = last_job;
		last_job = last_job->next;
	}
	last_job->and_inst = init_inst(NULL);
	add_redir(last_job->and_inst, name, node->type);
	return (last_job->and_inst);
}

t_inst				*redir_in_new_inst(t_lexer *node, t_parse *tree, char **tab)
{
	t_inst		*inst;

	inst = NULL;
	if (node->prev == NULL || node->prev->type == SEP)
		inst = add_redir_newcmd(node, tree, *tab);
	else if (node->prev->type == PIPE)
		inst = add_redir_inpipe(node, tree, *tab);
	else if (node->prev->type == OR)
		inst = add_redir_inor(node, tree, *tab);
	else if (node->prev->type == AND)
		inst = add_redir_inand(node, tree, *tab);
	return (inst);
}
