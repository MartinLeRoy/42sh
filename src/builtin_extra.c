/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcohen <dcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 18:56:20 by dcohen            #+#    #+#             */
/*   Updated: 2014/03/27 20:41:27 by dcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_sh.h"
#include "termcaps.h"
#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_puthelp(char *str)
{
	tputs(tgetstr("us", NULL), 1, tputchar);
	ft_putstr("usage:");
	tputs(tgetstr("me", NULL), 1, tputchar);
	ft_putchar(' ');
	ft_putstr(str);
}

int		sh_help(char **req, char ***env)
{
	(void)req;
	(void)env;
	tputs(tgetstr("mr", NULL), 1, tputchar);
	ft_putendl("Welcome to the help page of 42sh:");
	tputs(tgetstr("me", NULL), 1, tputchar);
	ft_putchar('\n');
	ft_puthelp("cd [path] : ");
	ft_putendl("change current directory");
	ft_puthelp("echo [-n] [name] : ");
	ft_putendl("write arguments to the standard output");
	ft_puthelp("env [-i] [command] : ");
	ft_putendl("show current environment");
	ft_puthelp("exit : ");
	ft_putendl("quit the terminal");
	ft_puthelp("export [-n] [-] [name=value] : ");
	ft_putendl("set the export attribute for variables");
	ft_puthelp("history : ");
	ft_putendl("show history of current session");
	ft_puthelp("setenv [name=value] : ");
	ft_putendl("set variable for current environment");
	ft_puthelp("unsetenv [name=value] : ");
	ft_putendl("unset variable for current environment");
	ft_puthelp("42sh [name.sh] : ");
	ft_putendl("execute shell script");
	return (0);
}

int		open_script(char *name)
{
	int		fd;
	char	*find;

	find = ft_strstr(name, ".sh");
	if ((!find) || (find && find[3] != '\0'))
	{
		ft_putendl("42sh: Bad format, .sh needed");
		return (-1);
	}
	if ((fd = open(name, O_RDONLY)) == -1)
	{
		ft_putstr("42sh: ");
		ft_putstr(name);
		ft_putendl(": No such file or no permissions");
		return (-1);
	}
	return (fd);
}

int		sh_script(char **req, char ***env)
{
	int		fd;
	int		ret;
	char	*line;

	if (req[1])
	{
		if ((fd = open_script(req[1])) == -1)
			return (-1);
		while ((ret = get_next_line(fd, &line)))
		{
			if (line[0] != '#')
				sh_treat_command(&line, env);
			free(line);
		}
		close(fd);
		if (ret == -1)
			return (-1);
		free(line);
	}
	return (0);
}
