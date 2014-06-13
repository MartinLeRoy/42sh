/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_check_syntax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 17:10:46 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/26 19:10:00 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "lexer.h"
#include "libft.h"

static int			syntax_error(t_lexer *node)
{
	write(2, "42sh: syntax error near unexpected token `", 42);
	ft_putstr_fd(node->str, 2);
	write(2, "\'\n", 2);
	return (-1);
}

static t_lexer		*remove_node_inlex(t_lexer *node, t_lx *lex)
{
	t_lexer		*node_ret;

	node_ret = node->next;
	if (node->prev == NULL && node->next)
	{
		lex->first = node->next;
		node->next->prev = NULL;
	}
	else if (node->prev && node->next)
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	else if (node->next == NULL && node->prev)
	{
		lex->last = node->prev;
		node->prev->next = NULL;
	}
	else if (node->prev == NULL && node->next == NULL)
	{
		lex->first = NULL;
		lex->last = NULL;
	}
	free_node_lex(node);
	return (node_ret);
}

static int			is_quote_empty(t_lexer *node)
{
	char	quote;
	int		i;

	i = 1;
	quote = (node->str)[0];
	while ((node->str)[i])
	{
		if (!ft_isspace((node->str)[i]) && (node->str)[i] != quote)
			return (0);
		i++;
	}
	return (1);
}

static void			check_empty_node(t_lx *lex)
{
	t_lexer		*node;

	node = lex->first;
	while (node)
	{
		if (node->str == NULL)
			node = remove_node_inlex(node, lex);
		else if (node->str && (node->str)[0] == '\0')
			node = remove_node_inlex(node, lex);
		else if (node->type > 0 && node->type < 4 && is_quote_empty(node))
			node = remove_node_inlex(node, lex);
		else
			node = node->next;
	}
}

int					check_syntax(t_lx *lex)
{
	t_lexer		*node;

	check_empty_node(lex);
	node = lex->first;
	while (node)
	{
		if (node->prev == NULL && node->type > 3 && node->type < 8)
			return (syntax_error(node));
		if (node->next == NULL && node->type > 7)
			return (syntax_error(node));
		if (node->type > 3 && node->next && node->next->type == node->type)
			return (syntax_error(node));
		if (node->type > 7 && node->next && node->next->type > 3
			&& node->next->type < 8)
			return (syntax_error(node->next));
		if (node->type > 7 && node->next && node->next->type > 7
			&& node->next->type < 13)
			return (syntax_error(node->next));
		if (node->type > 3 && node->type < 8 && node->next
			&& node->next->type > 3 && node->next->type < 8)
			return (syntax_error(node->next));
		node = node->next;
	}
	return (0);
}
