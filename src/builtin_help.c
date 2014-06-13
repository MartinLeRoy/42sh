/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcohen <dcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 17:01:01 by dcohen            #+#    #+#             */
/*   Updated: 2014/03/27 20:41:31 by dcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_sh.h"
#include "termcaps.h"
#include "libft.h"

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
	return (0);
}
