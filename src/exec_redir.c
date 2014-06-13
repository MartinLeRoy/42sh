/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/22 16:52:52 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/25 20:26:25 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "exec_sh.h"
#include "parseur.h"
#include "libft.h"

static void			error_redir(char *name, char type)
{
	write(2, "42sh: ", 6);
	ft_putstr_fd(name, 2);
	if (type == REDIR_L)
	{
		if (access(name, F_OK) == -1)
			write(2, ": No such file or directory\n", 28);
		else if (access(name, F_OK | R_OK) == -1)
			write(2, ": Permission denied\n", 20);
	}
	else if (type > 8)
	{
		if (access(name, F_OK) == -1)
			write(2, ": Failed on creation\n", 21);
		else if (access(name, F_OK | W_OK))
			write(2, ": Permission denied\n", 20);
	}
	exit(-1);
}

static int			get_fd(char *name, char type)
{
	int		fd;

	fd = 0;
	if (type == REDIR_L)
	{
		if ((fd = open(name, O_RDONLY)) == -1)
			error_redir(name, REDIR_L);
	}
	else if (type > 8 && type <= 12)
	{
		fd = 1;
		if (type == APPEND_R)
		{
			if ((fd = open(name, O_WRONLY | O_APPEND | O_CREAT, 0644)) == -1)
				error_redir(name, type);
		}
		else if (type == REDIR_R || type == REDIR_D || type == REDIR_ER)
		{
			if ((fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1)
				error_redir(name, type);
		}
	}
	return (fd);
}

static void			redir_from_out(t_inst *inst, t_redir *redir)
{
	if (inst->fd_out != STDOUT)
		close(inst->fd_out);
	inst->fd_out = get_fd(redir->name, redir->type);
	if (redir->type == REDIR_D)
	{
		if (inst->fd_err != STDERR)
			close(inst->fd_err);
		inst->fd_err = dup(inst->fd_out);
	}
}

void				add_redir_to_inst(t_inst *inst, t_redir *redir)
{
	while (redir)
	{
		if (redir->type == REDIR_L)
		{
			if (inst->fd_in != STDIN)
				close(inst->fd_in);
			inst->fd_in = get_fd(redir->name, redir->type);
		}
		else if (redir->type > 8 && redir->type < 12)
			redir_from_out(inst, redir);
		else if (redir->type == REDIR_ER)
		{
			if (inst->fd_err != STDERR)
				close(inst->fd_err);
			inst->fd_err = get_fd(redir->name, redir->type);
		}
		redir = redir->next;
	}
}
