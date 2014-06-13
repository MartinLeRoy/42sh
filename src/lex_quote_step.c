/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_quote_step.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/19 19:07:26 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/26 16:21:11 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"

static int		is_quote_valid(int pos, t_lquote *quote_list)
{
	t_quote		*node;

	if (quote_list->first == NULL)
		return (0);
	node = quote_list->first;
	while (node)
	{
		if (pos == node->a || pos == node->b)
			return (-1);
		if (pos > node->a && pos < node->b)
			return (-1);
		node = node->next;
	}
	return (0);
}

static void		get_next(char **cmd_ptr, int pos, char quote, t_lquote *lquote)
{
	char		*more;
	char		*cmd;
	int			i;

	i = pos + 1;
	if (is_quote_valid(pos, lquote))
		return ;
	cmd = *cmd_ptr;
	while (cmd[i])
	{
		if (cmd[i] == quote)
		{
			add_quote_lst(lquote, pos, i, quote);
			return ;
		}
		i++;
	}
	more = get_more(quote);
	cat_cmd(cmd_ptr, &more, 1);
	get_next(cmd_ptr, pos, quote, lquote);
	return ;
}

static int		is_quote(char totest, char *cmd, int pos, char *quote)
{
	int			i;

	if (ft_isbslashed(cmd, pos))
		return (0);
	i = 0;
	while (quote[i])
	{
		if (quote[i] == totest)
			return (1);
		i++;
	}
	return (0);
}

static void		check_quote(char **cmd_ptr)
{
	int			i;
	char		*cmd;
	t_lquote	*quote_list;

	cmd = *cmd_ptr;
	quote_list = init_lquote();
	i = 0;
	while (cmd[i])
	{
		if (is_quote(cmd[i], cmd, i, "\"\'`"))
		{
			get_next(cmd_ptr, i, cmd[i], quote_list);
			cmd = *cmd_ptr;
		}
		i++;
	}
	free_quote_list(quote_list);
}

void			stp_quote(char **cmd, char **env)
{
	check_quote(cmd);
	if (is_cmd_finish(*cmd))
		stp_cmd_finish(cmd, env);
}
