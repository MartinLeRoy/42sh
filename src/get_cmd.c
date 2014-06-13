/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 17:10:14 by rabid-on          #+#    #+#             */
/*   Updated: 2014/03/27 17:23:15 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <signal.h>
#include "termcaps.h"
#include "libft.h"
#include <signal.h>

void	put_cmd(t_line *line, int flag)
{
	int		i;

	i = 0;
	while (i++ < line->cur)
		tputs(tgetstr("up", NULL), 1, tputchar);
	tputs(tgetstr("cr", NULL), 1, tputchar);
	tputs(tgetstr("cd", NULL), 1, tputchar);
	tputs(tgetstr("cr", NULL), 1, tputchar);
	if (flag)
		ft_putstr("\033[1;34m");
	else
		ft_putstr("\033[1;33m");
	ft_putstr(line->prompt);
	ft_putstr("\033[0m");
	ft_putstr(line->cmd);
	i = 0;
	while (i++ < line->cur)
		tputs(tgetstr("up", NULL), 1, tputchar);
	i = 0;
	while (i++ < line->cur)
		tputs(tgetstr("do", NULL), 1, tputchar);
	tputs(tgetstr("cr", NULL), 1, tputchar);
	i = 0;
	while (i++ < line->col)
		tputs(tgetstr("nd", NULL), 1, tputchar);
}

t_line	*which_key(char *key, t_line *line, int flag)
{
	struct winsize	win;
	int				w;
	int				h;

	ioctl(0, TIOCGWINSZ, &win);
	h = win.ws_row - (line->line + 1);
	w = (ft_strlen(line->cmd) + ft_strlen(line->prompt) + 1) % win.ws_col;
	if ((key[0] > 31 && key[0] < 127) && (h != 0 || w != 0))
		line = add_char(line, key[0], flag);
	else if ((LEFT) || (RIGHT) || (HOME) || (END))
		line = move_cursor(key, line);
	else if ((DEL) || (DEL2))
		line = del_char(key, line, flag);
	else if (((UP) || (DOWN)) && flag)
		line = prev_cmd(key, line, flag);
	else if (((TAB) || (OPTL) || (OPTR)) && flag)
		line = move_word(key, line, flag);
	else if ((OPTU) || (OPTD))
		line = move_line(key, line);
	return (line);
}

t_line	*size(t_line *line, char *key)
{
	struct winsize	win;
	int				s[2];

	ioctl(0, TIOCGWINSZ, &win);
	s[0] = win.ws_row - (line->line + 1);
	s[1] = (ft_strlen(line->cmd) + ft_strlen(line->prompt) + 1)
			% win.ws_col;
	if (s[0] != 0 || s[1] != 0)
		line = check_size(line, key);
	return (line);
}

char	*get_cmd(t_line *line, int flag)
{
	char			key[9];

	if (flag)
		line->key = ft_strdup("");
	line->cmd = ft_strdup("");
	while (42)
	{
		ft_bzero(key, 9);
		read(0, key, 8);
		line = singleton_line(NULL);
		if ((CTRLC) || (RETURN) || (CTRLD))
			return (exit_prompt(key, line, flag));
		else
			line = which_key(key, line, flag);
		line = size(line, key);
		if (flag)
		{
			free(line->key);
			line->key = ft_strdup(key);
		}
		singleton_line(line);
	}
	return (line->cmd);
}
