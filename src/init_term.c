/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 20:33:47 by rabid-on          #+#    #+#             */
/*   Updated: 2014/03/27 15:44:21 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "termcaps.h"

int		tputchar(int c)
{
	write(1, &c, 1);
	return (1);
}

void	restore_env(int flag)
{
	struct termios	term;

	tcgetattr(0, &term);
	if (flag)
	{
		tputs(tgetstr("te", NULL), 1, tputchar);
		term.c_lflag |= ISIG;
	}
	term.c_lflag |= ICANON;
	term.c_lflag |= ECHO;
	tcsetattr(0, 0, &term);
}

t_term	init_term(int flag)
{
	struct termios	term;

	tgetent(NULL, getenv("TERM"));
	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ISIG);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, 0, &term);
	if (flag)
		tputs(tgetstr("ti", NULL), 1, tputchar);
	return (term);
}
