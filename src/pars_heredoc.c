/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 20:30:50 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/25 20:42:28 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "parseur.h"
#include "lexer.h"
#include "termcaps.h"

static void			heredoc_next_cmd(t_lexer *node, t_inst *inst, char **tab)
{
	t_lexer		*nd_next;

	nd_next = node->next;
	if (tab[1] == NULL && inst->arg == NULL && inst->redir == NULL)
	{
		if (nd_next->next == NULL || (nd_next->next->type > 3
								&& nd_next->next->type < 8))
		{
			inst->prev->next = NULL;
			free_inst(inst);
		}
		return ;
	}
	else
		cat_cmd_pars(inst, tab, 1);
}

static int			get_next_heredoc(char **tmp, char *buf, char *stop)
{
	char		*add;

	if (!ft_strncmp(buf, stop, ft_strlen(stop)))
		return (1);
	add = ft_strjoinwsep(*tmp, buf, ' ');
	free(*tmp);
	*tmp = add;
	return (0);
}

static char			**get_heredoc(char *stop)
{
	char		*buf;
	char		*tmp;
	char		**heredoc;

	tmp = ft_strdup("heredoc_builtin_sh");
	while (42)
	{
		buf = get_entry("<heredoc> ");
		write(1, "\n", 1);
		if (get_next_heredoc(&tmp, buf, stop))
			break ;
		if (buf)
			free(buf);
	}
	if (buf)
		free(buf);
	heredoc = ft_strsplit(tmp, ' ');
	free(tmp);
	return (heredoc);
}

t_lexer				*add_heredoc(t_lexer *node, t_parse *tree)
{
	char		**tab;
	char		**heredoc;
	t_inst		*ret;

	tab = NULL;
	if (node->next && node->next->type == CMD)
		tab = ft_strsplitspace(node->next->str);
	else if (node->next && node->next->type > 0 && node->next->type < 4)
		tab = ft_strsplit(node->next->str, '\0');
	heredoc = get_heredoc(*tab);
	if (node->prev == NULL || (node->prev->type > 3 && node->prev->type < 8))
		ret = heredoc_new_inst(node, tree, &heredoc);
	else
		ret = heredoc_b4_inst(tree, &heredoc);
	heredoc_next_cmd(node, ret, tab);
	ft_tabfree(&tab);
	return (node->next->next);
}

int					check_heredoc(t_lexer *node)
{
	if (node->type == 13 && node->next)
		return (1);
	return (0);
}
