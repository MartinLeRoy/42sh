/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_search_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 21:02:09 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/25 20:38:58 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "parseur.h"

int			is_job_free(t_job *job)
{
	if (job->inst || job->and_inst || job->or_inst)
		return (0);
	return (1);
}

t_job		*find_last_job(t_parse *tree)
{
	t_cmd	*bws_cmd;
	t_job	*bws_job;

	bws_cmd = tree->cmd;
	while (bws_cmd->next)
		bws_cmd = bws_cmd->next;
	if (bws_cmd->job == NULL)
	{
		bws_cmd->job = init_job();
		return (bws_cmd->job);
	}
	else
	{
		bws_job = bws_cmd->job;
		while (bws_job->next)
			bws_job = bws_job->next;
		return (bws_job);
	}
}

int			is_inst_free(t_inst *inst)
{
	if (inst->arg == NULL)
		return (1);
	return (0);
}

t_inst		*find_last_inst(t_parse *tree)
{
	t_job	*last_job;
	t_inst	*bws_inst;

	last_job = find_last_job(tree);
	bws_inst = NULL;
	if (!is_job_free(last_job))
	{
		if (last_job->inst)
			bws_inst = last_job->inst;
		else if (last_job->and_inst)
			bws_inst = last_job->and_inst;
		else if (last_job->or_inst)
			bws_inst = last_job->or_inst;
		while (bws_inst->next)
			bws_inst = bws_inst->next;
	}
	return (bws_inst);
}
