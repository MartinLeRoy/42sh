/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 20:33:04 by rabid-on          #+#    #+#             */
/*   Updated: 2014/03/27 16:48:53 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "termcaps.h"
#include "parseur.h"
#include "lexer.h"
#include "forty_two_sh.h"
#include "exec_sh.h"

void	sh_treat_command(char **cmd, char ***env)
{
	t_lx	*lex;
	t_parse	*tree;

	if (sh_lexer(&lex, cmd, *env))
		return ;
	tree = init_tree(env);
	sh_parsing(lex, tree);
	if (!check_parsing(tree))
		sh_exec(tree);
	free_lex(lex);
	free_pars(tree);
}

char	***single_env(char ***env)
{
	static char		***sing_env;

	if (env)
		sing_env = env;
	return (sing_env);
}

void	print_names(void)
{
	tputs(tgetstr("mr", NULL), 1, tputchar);
	ft_putendl("42sh by dcohen, jchenaf, mle-roy, rabid-on, sgueronn");
	tputs(tgetstr("me", NULL), 1, tputchar);
}

void	forty_two_sh(t_line *line, char ***env)
{
	while (42)
	{
		check_env(env);
		single_env(env);
		init_term(0);
		line = init_line(line, *env);
		ft_putstr("\033[1;34m");
		ft_putstr(line->prompt);
		ft_putstr("\033[0m");
		line->cmd = get_cmd(line, 1);
		write(1, "\n", 1);
		line = add_history(line);
		restore_env(0);
		sh_treat_command(&(line->cmd), env);
	}
}

int		main(void)
{
	struct termios	term;
	char			**env;
	t_line			*line;

	(void)term;
	catch_signal();
	env = sh_envinit();
	term = init_term(1);
	print_names();
	line = NULL;
	forty_two_sh(line, &env);
	return (0);
}
