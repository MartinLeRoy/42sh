/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_make.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/13 19:26:57 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/21 19:04:39 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "libft.h"

static void			add_operator(t_lx *lex, int ret, char *tolex)
{
	t_lexer		*token;

	token = new_token();
	token->str = ft_strsub(tolex, 0, ret);
	token->type = lex_get_type(token->str);
	add_token(lex, token);
}

static void			add_to_lex(char *cmd, char *tolex, t_lx *lex, int ret)
{
	t_lexer		*token;
	char		*tmp;

	if ((tolex - cmd) > 0)
	{
		token = new_token();
		tmp = ft_strsub(cmd, 0, (tolex - cmd));
		token->str = ft_strtrim(tmp);
		free(tmp);
		add_token(lex, token);
	}
	if (*tolex)
		add_operator(lex, ret, tolex);
}

static int			check_key(char *ptr, int pos, char *cmd)
{
	static char		*key_2[] = {">>", "<<", "&&", "||", "&>", "2>", "1>", NULL};
	static char		key_one[] = "\"\'`><|;";
	int				ret;
	int				i;

	i = 0;
	while (key_2[i])
	{
		if (!ft_strncmp(ptr, key_2[i], 2))
			return (2);
		i++;
	}
	i = 0;
	ret = 1;
	while (key_one[i])
	{
		if (key_one[i] == *ptr)
		{
			if (lex_isquote(ptr, pos, cmd))
				ret = browse_quote(ptr, pos, cmd);
			return (ret);
		}
		i++;
	}
	return (0);
}

void				make_lex(t_lx *lex, char *cmd)
{
	char	*tolex;
	int		ret;
	int		pos;

	pos = 0;
	ret = 0;
	tolex = cmd;
	while (*tolex)
	{
		if ((ret = check_key(tolex, pos, cmd)) && !ft_isbslashed(cmd, pos))
		{
			add_to_lex(cmd, tolex, lex, ret);
			tolex += ret;
			pos = 0;
			cmd = tolex;
		}
		else
		{
			pos++;
			tolex++;
		}
	}
	if (cmd != tolex)
		add_to_lex(cmd, tolex, lex, ret);
}
