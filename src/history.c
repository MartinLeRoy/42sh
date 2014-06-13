/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 17:51:57 by rabid-on          #+#    #+#             */
/*   Updated: 2014/03/27 00:05:25 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "termcaps.h"
#include "libft.h"

t_hist	*add_list(t_hist *hist, char *cmd)
{
	t_hist	*elem;

	elem = (t_hist *)malloc(sizeof(t_hist));
	elem->cmd = ft_strdup(cmd);
	elem->next = hist;
	elem->prev = NULL;
	if (hist)
		hist->prev = elem;
	return (elem);
}

int		add_file(t_line *line)
{
	int		fd;

	fd = open(line->path_hist, O_RDWR | O_APPEND | O_CREAT, 0666);
	if (fd == -1)
		return (-1);
	ft_putendl_fd(line->cmd, fd);
	close(fd);
	return (line->fd);
}

t_line	*add_history(t_line *line)
{
	if (line->cmd[0] != '\0')
	{
		line->fd = add_file(line);
		line->hist = add_list(line->hist, line->cmd);
		line->nb_hist++;
	}
	return (line);
}
