/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/22 23:00:10 by rabid-on          #+#    #+#             */
/*   Updated: 2014/03/26 20:19:27 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"
#include "libft.h"
#include <sys/ioctl.h>
#include <stdlib.h>

t_line	*move_cursorend(t_line *line)
{
	int				i;
	struct winsize	win;

	i = 0;
	ioctl(0, TIOCGWINSZ, &win);
	line->pos = ft_strlen(line->prompt) + ft_strlen(line->cmd);
	line->col = (ft_strlen(line->prompt) + ft_strlen(line->cmd)) % win.ws_col;
	while (line->cur++ < line->line)
		tputs(tgetstr("do", NULL), 1, tputchar);
	tputs(tgetstr("cr", NULL), 1, tputchar);
	while (i++ < line->col)
		tputs(tgetstr("nd", NULL), 1, tputchar);
	line->cur = line->line;
	return (line);
}

t_line	*move_cursorhome(t_line *line)
{
	int		i;

	i = 0;
	line->pos = ft_strlen(line->prompt);
	line->col = line->pos;
	while (line->cur-- > 0)
		tputs(tgetstr("up", NULL), 1, tputchar);
	tputs(tgetstr("cr", NULL), 1, tputchar);
	while (i++ < line->col)
		tputs(tgetstr("nd", NULL), 1, tputchar);
	line->cur = 0;
	return (line);
}

t_line	*move_cursor(char *key, t_line *line)
{
	int		c;

	c = ft_strlen(line->cmd) + ft_strlen(line->prompt);
	if (LEFT && (line->pos > (int)ft_strlen(line->prompt)))
	{
		tputs(tgetstr("le", NULL), 1, tputchar);
		line->pos--;
		line->col--;
	}
	else if (RIGHT && line->pos < c)
	{
		tputs(tgetstr("nd", NULL), 1, tputchar);
		line->pos++;
		line->col++;
	}
	else if (HOME)
		line = move_cursorhome(line);
	else if (END)
		line = move_cursorend(line);
	return (line);
}
