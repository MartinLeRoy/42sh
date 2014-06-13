/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/22 17:10:43 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/25 20:25:07 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "exec_sh.h"
#include "parseur.h"

static void			exec_inst(t_inst *inst, t_parse *tree)
{
	if (inst->redir)
		add_redir_to_inst(inst, inst->redir);
	if (inst->fd_err != STDERR)
		ft_dup2(inst->fd_err, 2);
	if (inst->fd_in != STDIN)
		ft_dup2(inst->fd_in, 0);
	if (inst->fd_out != STDOUT)
		ft_dup2(inst->fd_out, 1);
	exec_cmd(inst, tree);
}

static void			exec_and(t_inst *inst, t_parse *tree, int ret)
{
	if (ret != 0)
		exit(-1);
	else
	{
		if (is_inst_alone(inst))
			exec_inst(inst, tree);
		else
			exec_pipe(inst, tree);
	}
}

static void			exec_or(t_inst *inst, t_parse *tree, int ret)
{
	if (ret != 0)
	{
		if (is_inst_alone(inst))
			exec_inst(inst, tree);
		else
			exec_pipe(inst, tree);
	}
	else
		exit(0);
}

void				exec_job(t_cmd *cmd, t_parse *tree)
{
	t_job	*job;
	pid_t	ret;
	pid_t	pid;

	ret = 0;
	job = cmd->job;
	while (job)
	{
		if ((pid = fork()) == 0)
		{
			if (job->inst && is_inst_alone(job->inst))
				exec_inst(job->inst, tree);
			else if (job->inst && !is_inst_alone(job->inst))
				exec_pipe(job->inst, tree);
			else if (job->and_inst)
				exec_and(job->and_inst, tree, ret);
			else if (job->or_inst)
				exec_or(job->or_inst, tree, ret);
		}
		else
			waitpid(pid, &ret, WUNTRACED);
		job = job->next;
	}
}
