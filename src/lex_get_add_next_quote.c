/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_get_add_next_quote.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 18:19:40 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/26 16:10:56 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "lexer.h"
#include "libft.h"
#include "termcaps.h"

static int			get_next_quote(char **more, char *buf, char quote)
{
	char	*new;
	int		i;

	i = 0;
	if (*more == NULL)
		*more = ft_strdup(buf);
	else
	{
		new = ft_strjoinwsep(*more, buf, '\n');
		free(*more);
		*more = new;
	}
	while ((*more)[i])
	{
		if ((*more)[i] == quote)
			return (1);
		i++;
	}
	return (0);
}

static char			*get_quote_prompt(char quote)
{
	static char		*quote_prmt[] =

	{
	"<dquote> ",
	"<squote> ",
	"<bquote> "
	};
	if (quote == '"')
		return (quote_prmt[0]);
	else if (quote == '\'')
		return (quote_prmt[1]);
	else if (quote == '`')
		return (quote_prmt[2]);
	return (NULL);
}

char				*get_more(char quote)
{
	char		*buf;
	char		*more;
	char		*ptr;

	more = NULL;
	ptr = get_quote_prompt(quote);
	while (42)
	{
		buf = get_entry(ptr);
		write(1, "\n", 1);
		if (get_next_quote(&more, buf, quote))
			break ;
		free(buf);
	}
	free(buf);
	return (more);
}

void				add_quote_lst(t_lquote *lquote, int a, int b, char quote)
{
	t_quote		*node;

	node = init_quote(a, b, quote);
	if (lquote->first == NULL)
	{
		lquote->first = node;
		lquote->last = node;
	}
	else
	{
		lquote->last->next = node;
		node->prev = lquote->last;
		lquote->last = node;
	}
}
