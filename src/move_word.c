/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 22:40:23 by rabid-on          #+#    #+#             */
/*   Updated: 2014/03/27 17:18:17 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "termcaps.h"

t_line	*move_word2(char *key, t_line *line, int i, int flag)
{
	int		end;
	int		c;

	c = line->pos - ft_strlen(line->prompt);
	end = ft_strlen(line->cmd) + (int)ft_strlen(line->prompt);
	if (OPTR)
	{
		while (((line->cmd[c] != ' ' && line->cmd[c] != '\t') || i == 1)
				&& line->pos < end)
		{
			i = 0;
			tputs(tgetstr("nd", NULL), 1, tputchar);
			line->col++;
			line->pos++;
			c++;
			line = check_size(line, key);
		}
	}
	else if (TAB)
		line = do_tab(line, flag);
	return (line);
}

t_line	*move_word(char *key, t_line *line, int flag)
{
	int		i;
	int		c;

	i = 0;
	c = line->pos - ft_strlen(line->prompt);
	if (line->cmd[c] != ' ' || line->cmd[c] != '\t')
		i = 1;
	if (OPTL)
	{
		while (((line->cmd[c] != ' ' && line->cmd[c] != '\t') || i == 1)
				&& line->pos > (int)ft_strlen(line->prompt))
		{
			i = 0;
			tputs(tgetstr("le", NULL), 1, tputchar);
			line->col--;
			line->pos--;
			c--;
			line = check_size(line, key);
		}
	}
	else
		line = move_word2(key, line, i, flag);
	return (line);
}
