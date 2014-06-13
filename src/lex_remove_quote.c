/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_remove_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 17:27:59 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/21 17:28:53 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "libft.h"

static void			del_quote(t_lexer *node)
{
	int		len;
	char	*str;

	str = node->str;
	str[0] = '\0';
	ft_strcat(str, &str[1]);
	len = ft_strlen(str);
	str[len - 1] = '\0';
}

void				remove_quote(t_lx *lex, char **env)
{
	t_lexer		*browse_lx;

	(void)env;
	if (lex == NULL)
		return ;
	browse_lx = lex->first;
	while (browse_lx)
	{
		if (browse_lx->type > 0 && browse_lx->type < 4)
			del_quote(browse_lx);
		browse_lx = browse_lx->next;
	}
}
