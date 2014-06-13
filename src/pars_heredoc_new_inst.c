/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_heredoc_new_inst.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 20:40:37 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/24 20:01:30 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "parseur.h"

static t_inst	*add_hdoc_newcmd(t_lexer *node, t_parse *tree, char ***heredoc)
{
	t_cmd		*bws_cmd;

	if (node->prev == NULL)
		add_cmd_tree(tree);
	bws_cmd = tree->cmd;
	while (bws_cmd->next)
		bws_cmd = bws_cmd->next;
	bws_cmd->job = init_job();
	bws_cmd->job->inst = init_inst(NULL);
	bws_cmd->job->inst->arg = *heredoc;
	bws_cmd->job->inst->next = init_inst(NULL);
	bws_cmd->job->inst->next->prev = bws_cmd->job->inst;
	return (bws_cmd->job->inst->next);
}

static t_inst	*add_hdoc_inpipe(t_parse *tree, char ***heredoc)
{
	t_inst		*last_inst;
	t_inst		*new;

	last_inst = find_last_inst(tree);
	new = init_inst(NULL);
	new->arg = *heredoc;
	last_inst->next = new;
	new->prev = last_inst;
	new->next = init_inst(NULL);
	new->next->prev = new;
	return (new->next);
}

static t_inst	*add_hdoc_inor(t_parse *tree, char ***heredoc)
{
	t_job		*last_job;
	t_inst		*new;

	last_job = find_last_job(tree);
	if (!is_job_free(last_job))
	{
		last_job->next = init_job();
		last_job->next->prev = last_job;
		last_job = last_job->next;
	}
	new = init_inst(NULL);
	new->arg = *heredoc;
	last_job->or_inst = new;
	new->next = init_inst(NULL);
	new->next->prev = new;
	return (new->next);
}

static t_inst	*add_hdoc_inand(t_parse *tree, char ***heredoc)
{
	t_job		*last_job;
	t_inst		*new;

	last_job = find_last_job(tree);
	if (!is_job_free(last_job))
	{
		last_job->next = init_job();
		last_job->next->prev = last_job;
		last_job = last_job->next;
	}
	new = init_inst(NULL);
	new->arg = *heredoc;
	last_job->and_inst = new;
	new->next = init_inst(NULL);
	new->next->prev = new;
	return (new->next);
}

t_inst			*heredoc_new_inst(t_lexer *node, t_parse *tree, char ***heredoc)
{
	t_inst		*inst;

	inst = NULL;
	if (node->prev == NULL || node->prev->type == SEP)
		inst = add_hdoc_newcmd(node, tree, heredoc);
	else if (node->prev->type == PIPE)
		inst = add_hdoc_inpipe(tree, heredoc);
	else if (node->prev->type == OR)
		inst = add_hdoc_inor(tree, heredoc);
	else if (node->prev->type == AND)
		inst = add_hdoc_inand(tree, heredoc);
	return (inst);
}
