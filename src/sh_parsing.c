/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/15 16:31:26 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/26 15:28:22 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parseur.h"
#include "lexer.h"
#include "libft.h"

void				add_redir(t_inst *inst, char *name, char type)
{
	t_redir		*redir;

	if (inst->redir == NULL)
		inst->redir = init_redir(name, type);
	else
	{
		redir = inst->redir;
		while (redir->next)
			redir = redir->next;
		redir->next = init_redir(name, type);
	}
}

void				cat_cmd_pars(t_inst *inst, char **tab, int arg)
{
	if (inst->arg == NULL && tab[arg])
		inst->arg = ft_strsplit("", '\0');
	while (inst->arg && tab[arg])
	{
		ft_tab_realloc(&(inst->arg), tab[arg]);
		arg++;
	}
}

t_check_pars		*get_check_pars(void)
{
	static t_check_pars		parse[] =

	{
	{&check_inst, &add_inst},
	{&check_new_cmd, &add_new_cmd},
	{&check_redir, &add_redir_tree},
	{&check_pipe, &add_pipe},
	{&check_and, &add_and},
	{&check_or, &add_or},
	{&check_quote, &add_quote},
	{&check_heredoc, &add_heredoc},
	{NULL, NULL}
	};
	return (parse);
}

void				sh_parsing(t_lx *lex, t_parse *tree)
{
	t_check_pars	*parse;
	t_lexer			*node;
	int				fn;
	int				flag;

	parse = get_check_pars();
	node = lex->first;
	while (node)
	{
		fn = 0;
		flag = 0;
		while (parse[fn].check)
		{
			if (parse[fn].check(node))
			{
				node = parse[fn].add_node(node, tree);
				flag = 1;
				break ;
			}
			fn++;
		}
		if (flag == 0)
			node = node->next;
	}
}
