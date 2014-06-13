/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_quote_stp_init_free.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 18:13:10 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/25 20:34:59 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "libft.h"

t_quote				*init_quote(int a, int b, char quote)
{
	t_quote	*new;

	if ((new = (t_quote *)malloc(sizeof(*new))) == NULL)
		ft_exit("malloc", 1);
	new->a = a;
	new->b = b;
	new->type = quote;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_lquote			*init_lquote(void)
{
	t_lquote	*new;

	if ((new = (t_lquote *)malloc(sizeof(*new))) == NULL)
		ft_exit("malloc", 1);
	new->first = NULL;
	new->last = NULL;
	return (new);
}

void				free_quote_list(t_lquote *quote_list)
{
	t_quote		*node;
	t_quote		*tmp;

	node = quote_list->first;
	while (node)
	{
		tmp = node->next;
		free(node);
		node = tmp;
	}
	free(quote_list);
}
