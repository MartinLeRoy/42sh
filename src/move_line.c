/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 21:13:30 by rabid-on          #+#    #+#             */
/*   Updated: 2014/03/26 20:19:53 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include "termcaps.h"
#include "libft.h"
#include <stdlib.h>

t_line	*move_lineup(t_line *line, int size_col)
{
	int		c;
	int		i;

	i = 0;
	c = (ft_strlen(line->cmd) + ft_strlen(line->prompt)) % size_col;
	if (line->cur < line->line - 1 || (line->col < c))
	{
		line->pos = line->pos + size_col;
		tputs(tgetstr("do", NULL), 1, tputchar);
		while (i++ < line->col)
			tputs(tgetstr("nd", NULL), 1, tputchar);
		line->cur++;
	}
	else if (line->cur == line->line - 1)
	{
		tputs(tgetstr("do", NULL), 1, tputchar);
		tputs(tgetstr("cr", NULL), 1, tputchar);
		line->pos = ft_strlen(line->prompt) + ft_strlen(line->cmd);
		line->col = c;
		while (i++ < line->col)
			tputs(tgetstr("nd", NULL), 1, tputchar);
		line->cur++;
	}
	return (line);
}

t_line	*move_linedown(t_line *line)
{
	int		i;

	i = 0;
	tputs(tgetstr("up", NULL), 1, tputchar);
	line->pos = ft_strlen(line->prompt);
	line->col = line->pos;
	tputs(tgetstr("cr", NULL), 1, tputchar);
	while (i++ < line->col)
		tputs(tgetstr("nd", NULL), 1, tputchar);
	line->cur--;
	return (line);
}

t_line	*move_line(char *key, t_line *line)
{
	struct winsize	win;

	ioctl(0, TIOCGWINSZ, &win);
	if (OPTU)
	{
		if (line->cur > 1 || (line->col > (int)ft_strlen(line->prompt)))
		{
			line->pos = line->pos - win.ws_col;
			tputs(tgetstr("up", NULL), 1, tputchar);
			line->cur--;
		}
		else if (line->cur == 1)
			line = move_linedown(line);
	}
	else if (OPTD)
		line = move_lineup(line, win.ws_col);
	return (line);
}
