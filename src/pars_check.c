/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 18:56:10 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/21 19:08:15 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parseur.h"
#include "libft.h"

int			error_parsing(int nb)
{
	char	*errmsg[4];

	errmsg[0] = "42sh: parsing: undefined error\n";
	errmsg[1] = "42sh: parsing: empty command\n";
	errmsg[2] = "42sh: parsing: no instruction in command\n";
	errmsg[3] = "42sh: parsing: no argument in instruction\n";
	if (nb < 1 || nb > 3)
		ft_putstr(errmsg[0]);
	else
		ft_putstr(errmsg[nb]);
	return (-1);
}

int			check_pars_inst(t_inst *inst)
{
	t_inst	*bws_inst;

	bws_inst = inst;
	while (bws_inst)
	{
		if (bws_inst->arg == NULL)
			return (3);
		bws_inst = bws_inst->next;
	}
	return (0);
}

int			check_pars_job(t_job *job)
{
	t_job	*bws_job;
	t_inst	*to_check;
	int		ret;

	bws_job = job;
	while (bws_job)
	{
		if (job->inst)
			to_check = job->inst;
		else if (job->and_inst)
			to_check = job->and_inst;
		else if (job->or_inst)
			to_check = job->or_inst;
		else
			return (2);
		if ((ret = check_pars_inst(to_check)))
			return (ret);
		bws_job = bws_job->next;
	}
	return (0);
}

int			check_parsing(t_parse *tree)
{
	t_cmd	*cmd;
	int		ret;

	cmd = tree->cmd;
	while (cmd)
	{
		if (cmd->job == NULL)
			return (error_parsing(1));
		else if ((ret = check_pars_job(cmd->job)))
			return (error_parsing(ret));
		cmd = cmd->next;
	}
	return (0);
}
