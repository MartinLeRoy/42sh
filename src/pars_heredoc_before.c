/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_heredoc_before.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 20:45:11 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/19 21:13:02 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "parseur.h"

static void			heredoc_in_job(t_parse *tree, t_inst *new)
{
	t_job		*last_job;

	last_job = find_last_job(tree);
	if (last_job->and_inst)
	{
		last_job->and_inst->prev = new;
		new->next = last_job->and_inst;
		last_job->and_inst = new;
	}
	else if (last_job->or_inst)
	{
		last_job->or_inst->prev = new;
		new->next = last_job->or_inst;
		last_job->or_inst = new;
	}
	else
	{
		if (last_job->inst)
		{
			last_job->inst->prev = new;
			new->next = last_job->inst;
		}
		last_job->inst = new;
	}
}

t_inst				*heredoc_b4_inst(t_parse *tree, char ***heredoc)
{
	t_inst		*last_inst;
	t_inst		*new;

	last_inst = find_last_inst(tree);
	new = init_inst(NULL);
	new->arg = *heredoc;
	if (last_inst->prev)
	{
		new->prev = last_inst->prev;
		last_inst->prev->next = new;
		new->next = last_inst;
		last_inst->prev = new;
	}
	else
		heredoc_in_job(tree, new);
	return (last_inst);
}
