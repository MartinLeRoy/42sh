/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 23:20:03 by rabid-on          #+#    #+#             */
/*   Updated: 2014/03/27 17:24:10 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/ioctl.h>
#include "forty_two_sh.h"
#include "libft.h"
#include "termcaps.h"

char	*exit_prompt(char *key, t_line *line, int flag)
{
	if ((CTRLC) || (RETURN))
		put_cmd(line, flag);
	if (CTRLC)
	{
		free(line->cmd);
		return (ft_strdup(""));
	}
	else if (RETURN)
	{
		while (line->cur++ < line->line)
			tputs(tgetstr("do", NULL), 1, tputchar);
		return (line->cmd);
	}
	else if (CTRLD)
	{
		if (flag)
		{
			free(line->cmd);
			return (ft_strdup("exit"));
		}
		else
			forty_two_sh(line, single_env(NULL));
	}
	return (line->cmd);
}

t_line	*prev_cmd(char *key, t_line *line, int flag)
{
	t_hist			*tmp;
	struct winsize	win;
	int				i;

	i = 1;
	ioctl(0, TIOCGWINSZ, &win);
	if (!line->hist)
		return (line);
	tmp = line->hist;
	if ((UP) && line->cpt_hist < line->nb_hist)
		line->cpt_hist++;
	else if ((DOWN) && line->cpt_hist > 1)
		line->cpt_hist--;
	while (tmp->next && i++ < line->cpt_hist)
		tmp = tmp->next;
	free(line->cmd);
	line->cmd = ft_strdup(tmp->cmd);
	line->line = (ft_strlen(line->cmd) + ft_strlen(line->prompt)) / win.ws_col;
	line->col = (ft_strlen(line->cmd) + ft_strlen(line->prompt)) % win.ws_col;
	line->pos = ft_strlen(line->cmd) + ft_strlen(line->prompt);
	put_cmd(line, flag);
	line->cur = line->line;
	return (line);
}
