/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 23:20:37 by rabid-on          #+#    #+#             */
/*   Updated: 2014/03/27 20:41:34 by dcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "exec_sh.h"
#include "termcaps.h"
#include "get_next_line.h"

int		sh_exclam(char **req, char ***env)
{
	t_line	*line;
	t_hist	*hist;

	if (req[1] == NULL || req[1][0] == '!')
		return (0);
	line = singleton_line(NULL);
	hist = line->hist;
	while (hist && ft_strncmp(hist->cmd, req[1], ft_strlen(req[1])))
		hist = hist->next;
	if (!hist)
		return (-1);
	ft_putendl(hist->cmd);
	sh_treat_command(&hist->cmd, env);
	return (0);
}

void	ft_puthistory(int nb, char *str)
{
	ft_putnbr(nb);
	ft_putchar('\t');
	ft_putendl(str);
}

int		sh_history(char **request, char ***env)
{
	char	*cmd;
	int		fd;
	int		ret;
	int		i;
	char	*path;

	i = 1;
	ret = 0;
	(void)request;
	(void)env;
	if ((path = singleton_path(NULL)) == NULL
		|| (fd = open(path, O_RDONLY)) == -1)
		return (-1);
	while ((ret = get_next_line(fd, &cmd)) > 0)
	{
		if (cmd[0] != '\0')
			ft_puthistory(i, cmd);
		i++;
		free(cmd);
	}
	close(fd);
	if (ret == -1)
		return (-1);
	free(cmd);
	return (0);
}
