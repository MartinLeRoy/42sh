/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 21:08:36 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/22 19:27:19 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "lexer.h"
#include "parseur.h"

void		free_redir(t_redir *redir)
{
	t_redir		*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->name)
			free(redir->name);
		free(redir);
		redir = tmp;
	}
}

void		free_inst(t_inst *inst)
{
	t_inst		*tmp;

	while (inst)
	{
		tmp = inst->next;
		if (inst->arg)
			ft_tabfree(&(inst->arg));
		if (inst->fd_in != 0)
			close(inst->fd_in);
		if (inst->fd_out != 1)
			close(inst->fd_out);
		if (inst->fd_err != 2)
			close(inst->fd_err);
		if (inst->redir)
			free_redir(inst->redir);
		free(inst);
		inst = tmp;
	}
}

void		free_job(t_job *job)
{
	t_job	*tmp;

	while (job)
	{
		tmp = job->next;
		if (job->inst)
			free_inst(job->inst);
		if (job->and_inst)
			free_inst(job->and_inst);
		if (job->or_inst)
			free_inst(job->or_inst);
		free(job);
		job = tmp;
	}
}

void		free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->job)
			free_job(cmd->job);
		free(cmd);
		cmd = tmp;
	}
}

void		free_pars(t_parse *tree)
{
	if (tree->cmd)
		free_cmd(tree->cmd);
	ft_tabfree(&(tree->path));
	free(tree);
}
