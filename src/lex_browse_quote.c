/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_browse_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 17:42:10 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/21 17:45:21 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int					lex_isquote(char *tolex, int pos, char *cmd)
{
	if (*tolex == '\"' || *tolex == '\'' || *tolex == '`')
	{
		if (!ft_isbslashed(cmd, pos))
			return (1);
	}
	return (0);
}

static int			lex_is_samequote(char *ptr, int pos, char *cmd, char quote)
{
	if (lex_isquote(ptr, pos, cmd))
	{
		if (*ptr == quote)
			return (1);
		return (0);
	}
	return (0);
}

int					browse_quote(char *ptr, int pos, char *cmd)
{
	int		ret;
	char	quote;

	quote = *ptr;
	ret = 0;
	ptr++;
	while (*ptr && !lex_is_samequote(ptr, pos, cmd, quote))
	{
		pos++;
		ptr++;
		ret++;
	}
	if (!(*ptr))
		ret = 0;
	ret += 2;
	return (ret);
}
