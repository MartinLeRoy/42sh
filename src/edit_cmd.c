/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 17:15:18 by rabid-on          #+#    #+#             */
/*   Updated: 2014/03/27 17:45:36 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "termcaps.h"

t_line	*del_copy(t_line *line)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = (char *)malloc(sizeof(char) * ft_strlen(line->cmd));
	while (line->cmd[i] && i < line->pos - (int)ft_strlen(line->prompt) - 1)
	{
		tmp[i] = line->cmd[i];
		i++;
	}
	while (line->cmd[i + 1])
	{
		tmp[i] = line->cmd[i + 1];
		i++;
	}
	tmp[i] = '\0';
	free(line->cmd);
	line->cmd = ft_strdup(tmp);
	free(tmp);
	return (line);
}

t_line	*del_char(char *key, t_line *line, int flag)
{
	(void)key;
	if (line->pos == (int)ft_strlen(line->prompt))
		return (line);
	line = del_copy(line);
	if (line->pos > (int)ft_strlen(line->prompt))
	{
		line->col--;
		line->pos--;
	}
	put_cmd(line, flag);
	return (line);
}

t_line	*add_char(t_line *line, char c, int flag)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(line->cmd) + 2));
	while (i < line->pos - (int)ft_strlen(line->prompt))
	{
		tmp[i] = line->cmd[i];
		i++;
	}
	tmp[i] = c;
	while (line->cmd[i])
	{
		tmp[i + 1] = line->cmd[i];
		i++;
	}
	tmp[i + 1] = '\0';
	free(line->cmd);
	line->cmd = ft_strdup(tmp);
	line->pos++;
	line->col++;
	free(tmp);
	put_cmd(line, flag);
	return (line);
}
