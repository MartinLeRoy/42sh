/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 16:35:15 by rabid-on          #+#    #+#             */
/*   Updated: 2014/03/26 23:40:30 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "termcaps.h"

t_line	*singleton_line(t_line *line)
{
	static t_line	*s_line = NULL;

	if (line != NULL)
		s_line = line;
	return (s_line);
}

char	*singleton_path(char *path)
{
	static char	*s_path = NULL;

	if (path != NULL)
		s_path = path;
	return (s_path);
}
