/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 20:28:08 by rabid-on          #+#    #+#             */
/*   Updated: 2014/03/24 20:36:55 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"
#include <stdlib.h>

void	free_hist(t_hist *hist)
{
	t_hist	*tmp;

	while (hist)
	{
		tmp = hist->next;
		if (hist->cmd)
			free(hist->cmd);
		free(hist);
		hist = tmp;
	}
}

void	free_line(t_line *line)
{
	if (line->cmd)
		free(line->cmd);
	if (line->prompt)
		free(line->prompt);
	if (line->path_hist)
		free(line->path_hist);
	free_hist(line->hist);
	free(line);
}
