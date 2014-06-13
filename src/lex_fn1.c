/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_fn1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/13 19:34:43 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/25 20:32:39 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "libft.h"

t_lx		*init_lex(void)
{
	t_lx	*new;

	if ((new = (t_lx *)malloc(sizeof(*new))) == NULL)
		ft_exit(PROG, 1);
	new->first = NULL;
	new->last = NULL;
	return (new);
}

t_lexer		*new_token(void)
{
	t_lexer		*new;

	if ((new = (t_lexer *)malloc(sizeof(*new))) == NULL)
		ft_exit(PROG, 1);
	new->str = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->type = 0;
	return (new);
}

void		add_token(t_lx *lex, t_lexer *token)
{
	if (lex->first == NULL)
	{
		lex->first = token;
		lex->last = token;
	}
	else
	{
		token->prev = lex->last;
		lex->last->next = token;
		lex->last = token;
	}
}
