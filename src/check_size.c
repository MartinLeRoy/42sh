/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/22 20:54:01 by rabid-on          #+#    #+#             */
/*   Updated: 2014/03/27 17:22:18 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/ioctl.h>
#include "termcaps.h"
#include <stdlib.h>

t_line	*resize(t_line *line)
{
	struct winsize	win;
	int				c;

	c = ft_strlen(line->cmd) + ft_strlen(line->prompt);
	ioctl(0, TIOCGWINSZ, &win);
	line->line = c / win.ws_col;
	line->cur = line->pos / win.ws_col;
	line->col = line->pos % win.ws_col;
	put_cmd(line, 1);
	return (line);
}

t_line	*move_inlines2(char *key, t_line *line, int size_col, int *i)
{
	int		c;

	c = ft_strlen(line->cmd) + ft_strlen(line->prompt);
	if (line->pos < c && c % size_col == 0 && (key[0] > 31 && key[0] < 127))
	{
		while ((*i)++ < line->line - line->cur)
			tputs(tgetstr("up", NULL), 1, tputchar);
		line->line++;
	}
	return (line);
}

t_line	*move_inlines(t_line *line, char *key, int size_col)
{
	int		i;
	int		c;

	i = 0;
	c = ft_strlen(line->cmd) + ft_strlen(line->prompt);
	if (((DEL) || (DEL2)) && c % size_col == 0)
	{
		line->line--;
		if (line->col != 0)
		{
			while (i++ < line->line - line->cur)
				tputs(tgetstr("up", NULL), 1, tputchar);
		}
		else
			tputs(tgetstr("do", NULL), 1, tputchar);
	}
	else
		line = move_inlines2(key, line, size_col, &i);
	if (((DEL) || (DEL2) || (key[0] > 31 && key[0] < 127))
			&& line->line - line->cur > 0)
	{
		while (i++ < line->line - line->cur)
			tputs(tgetstr("up", NULL), 1, tputchar);
	}
	return (line);
}

t_line	*ascend_line(t_line *line, char *key, int size_col)
{
	int		i;
	int		c;

	i = 0;
	c = ft_strlen(line->cmd) + ft_strlen(line->prompt);
	line->col = size_col - 1;
	if ((DEL) || (DEL2) || (LEFT && line->pos >= c - 1))
	{
		while (i++ < line->line - line->cur + 1)
			tputs(tgetstr("up", NULL), 1, tputchar);
		if (((DEL) || (DEL2)) && line->pos >= c && line->line >= line->cur)
			tputs(tgetstr("do", NULL), 1, tputchar);
		i = 0;
		while (i++ < line->col)
			tputs(tgetstr("nd", NULL), 1, tputchar);
		line->cur--;
	}
	else if (line->pos < (int)ft_strlen(line->cmd)
			+ (int)ft_strlen(line->prompt))
		line->cur--;
	if (line->pos >= c - 1)
		line->line--;
	return (line);
}

t_line	*check_size(t_line *line, char *key)
{
	struct winsize	win;
	int				i;

	i = 0;
	ioctl(0, TIOCGWINSZ, &win);
	if (line->col == win.ws_col)
	{
		line->col = 0;
		if (key[0] > 31 && key[0] < 127 && line->cur != line->line)
		{
			while (i++ < line->line - line->cur - 1)
				tputs(tgetstr("up", NULL), 1, tputchar);
			tputs(tgetstr("cr", NULL), 1, tputchar);
		}
		else
			tputs(tgetstr("do", NULL), 1, tputchar);
		if (line->line == line->cur)
			line->line++;
		line->cur++;
	}
	else if (line->col == -1)
		line = ascend_line(line, key, win.ws_col);
	else
		line = move_inlines(line, key, win.ws_col);
	return (line);
}
