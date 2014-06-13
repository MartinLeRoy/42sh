/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_remove_bslash.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 17:24:52 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/26 18:47:13 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "libft.h"

static int			is_keysh(char *str, int pos, char *key_one)
{
	int				i;
	static char		*key_to[] =

	{">>", "<<", "&&", "||", "&>", "2>", "1>", NULL};
	i = 0;
	if (str[pos] == '\0')
		return (0);
	while (key_to[i])
	{
		if (!ft_strncmp(&str[pos], key_to[i], 2))
			return (1);
		i++;
	}
	i = 0;
	while (key_one[i])
	{
		if (key_one[i] == str[pos])
			return (1);
		i++;
	}
	return (0);
}

static void			removing_slash(t_lexer *node, int pos)
{
	char	*str;

	str = node->str;
	str[pos] = '\0';
	ft_strcat(str, &str[pos + 1]);
}

static void			checknremove(t_lexer *node)
{
	int		i;
	char	*str;

	i = 0;
	str = node->str;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (str[i] == '\\' && !ft_isbslashed(str, i)
			&& is_keysh(str, i + 1, "\"\'`><|;*~\\"))
		{
			removing_slash(node, i);
			str = node->str;
			i = ft_strlen(node->str);
		}
		else
			i--;
	}
}

void				remove_bslash(t_lx *lex, char **env)
{
	t_lexer		*browse_lx;

	(void)env;
	if (lex == NULL)
		return ;
	browse_lx = lex->first;
	while (browse_lx)
	{
		if (browse_lx->type == CMD)
			checknremove(browse_lx);
		browse_lx = browse_lx->next;
	}
}
