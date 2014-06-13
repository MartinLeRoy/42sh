/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/22 16:46:52 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/22 16:52:30 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "exec_sh.h"

static void			pipe_inst(t_inst *inst, t_parse *tree, int in, int out)
{
	if (inst->redir)
		add_redir_to_inst(inst, inst->redir);
	if (inst->fd_err != STDERR)
		ft_dup2(inst->fd_err, STDERR);
	if (inst->prev != NULL && inst->fd_in != STDIN)
		ft_dup2(inst->fd_in, STDIN);
	else if (in != STDIN)
		ft_dup2(in, STDIN);
	if (inst->fd_out != STDOUT)
		ft_dup2(inst->fd_out, STDOUT);
	else if (out != STDOUT)
		ft_dup2(out, STDOUT);
	exec_cmd(inst, tree);
}

static void			close_pipe(int infile, int outfile, t_inst *inst)
{
	if (infile != inst->fd_in)
		close(infile);
	if (outfile != inst->fd_out)
		close(outfile);
}

void				exec_pipe(t_inst *inst, t_parse *tree)
{
	int		pipex[2];
	pid_t	pid;
	int		infile;
	int		outfile;
	pid_t	ret;

	infile = inst->fd_in;
	while (inst)
	{
		if (inst->next)
		{
			pipe(pipex);
			outfile = pipex[1];
		}
		else
			outfile = inst->fd_out;
		if ((pid = fork()) == 0)
			pipe_inst(inst, tree, infile, outfile);
		close_pipe(infile, outfile, inst);
		infile = pipex[0];
		inst = inst->next;
	}
	waitpid(pid, &ret, WUNTRACED);
	exit(ret);
}
