/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 18:10:09 by rabid-on          #+#    #+#             */
/*   Updated: 2014/03/27 17:13:41 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "termcaps.h"
#include "libft.h"
#include "forty_two_sh.h"

t_line	*create_line(t_line *line)
{
	if ((line = (t_line *)malloc(sizeof(t_line))) == NULL)
		ft_exit("malloc", 1);
	line->nb_hist = 0;
	line->fd = -1;
	line->tab_cpt = 0;
	line->prompt = NULL;
	line->path_hist = NULL;
	line->hist = NULL;
	line->cmd = NULL;
	line->key = NULL;
	line->tab = NULL;
	return (line);
}

t_line	*init_line2(t_line *line, char *name)
{
	if (!line)
		line = create_line(line);
	if (line->prompt)
	{
		free(line->prompt);
		line->prompt = NULL;
	}
	if (line->cmd)
	{
		free(line->cmd);
		line->cmd = NULL;
	}
	line->prompt = ft_strdup(name);
	line->col = ft_strlen(line->prompt);
	line->pos = line->col;
	line->cur = 0;
	line->line = 0;
	singleton_line(line);
	return (line);
}

char	*get_entry(char *prompt)
{
	t_line			*line;
	char			*cmd;

	line = NULL;
	init_term(0);
	line = init_line2(line, prompt);
	ft_putstr("\033[1;33m");
	ft_putstr(line->prompt);
	ft_putstr("\033[0m");
	line->cmd = get_cmd(line, 0);
	cmd = ft_strdup(line->cmd);
	restore_env(0);
	free_line(line);
	return (cmd);
}

t_line	*get_path(t_line *line, char **env)
{
	char	*pwd;
	char	*tmp;
	int		j;

	if ((pwd = sh_getenv("PWD", env)) == NULL)
	{
		line->prompt = ft_strdup("[42sh] ");
		return (line);
	}
	if (!line->path_hist)
		line->path_hist = ft_strjoin(pwd, "/.history");
	singleton_path(line->path_hist);
	j = ft_strlen(pwd);
	while (j > 0 && pwd[j] != '/')
		j--;
	tmp = ft_strsub(pwd, j, ft_strlen(pwd) - j);
	line->prompt = ft_strjoin(tmp, " > ");
	free(tmp);
	tmp = ft_strdup(line->prompt);
	free(line->prompt);
	line->prompt = ft_strjoin("[42sh] ", tmp);
	free(tmp);
	free(pwd);
	return (line);
}

t_line	*init_line(t_line *line, char **env)
{
	if (!line)
		line = create_line(line);
	if (line->prompt)
	{
		free(line->prompt);
		line->prompt = NULL;
	}
	if (line->cmd)
	{
		free(line->cmd);
		line->cmd = NULL;
	}
	if (line->key)
	{
		free(line->key);
		line->key = NULL;
	}
	line = get_path(line, env);
	line->col = ft_strlen(line->prompt);
	line->pos = line->col;
	line->cpt_hist = 0;
	line->cur = 0;
	line->line = 0;
	singleton_line(line);
	return (line);
}
