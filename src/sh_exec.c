/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 19:14:35 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/22 19:16:22 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "parseur.h"
#include "libft.h"
#include "exec_sh.h"

void		ft_dup2(int old_fd, int new_fd)
{
	if ((dup2(old_fd, new_fd)) == -1)
		ft_exit("dup2", -1);
	close(old_fd);
}

int			is_inst_alone(t_inst *inst)
{
	if (inst->next == NULL)
		return (1);
	else
		return (0);
}

int			sh_exec(t_parse *tree)
{
	t_cmd		*cmd;

	if (tree == NULL)
		return (0);
	cmd = tree->cmd;
	while (cmd)
	{
		if (check_builtin_before(cmd, tree) == 1)
			exec_job(cmd, tree);
		cmd = cmd->next;
	}
	return (0);
}
