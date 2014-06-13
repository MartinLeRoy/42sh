/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 15:05:38 by rabid-on          #+#    #+#             */
/*   Updated: 2014/03/26 17:42:31 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include "termcaps.h"

void	handle_signal(int sig)
{
	t_line	*line;

	if (sig == SIGWINCH)
	{
		if ((line = singleton_line(NULL)) == NULL)
			return ;
		line = resize(line);
		singleton_line(line);
	}
}

void	catch_signal(void)
{
	signal(SIGWINCH, handle_signal);
}
