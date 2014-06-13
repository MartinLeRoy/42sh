/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/13 14:29:57 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/26 16:50:30 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "libft.h"

void				cat_cmd(char **cmd_ptr, char **str, int bsn)
{
	char		*new;

	new = ft_strnew(ft_strlen(*cmd_ptr) + ft_strlen(*str) + 1);
	new = ft_strcat(new, *cmd_ptr);
	if (bsn)
		new = ft_strcat(new, "\n");
	else
		new = ft_strcat(new, " ");
	new = ft_strcat(new, *str);
	free(*cmd_ptr);
	*cmd_ptr = new;
	free(*str);
	*str = NULL;
}

void				free_node_lex(t_lexer *node)
{
	if (node->str)
		free(node->str);
	free(node);
}

void				free_lex(t_lx *lex)
{
	t_lexer		*node;
	t_lexer		*tmp;

	node = lex->first;
	while (node)
	{
		tmp = node->next;
		free_node_lex(node);
		node = NULL;
		node = tmp;
	}
	free(lex);
}

int					sh_lexer(t_lx **lex, char **cmd, char **env)
{
	int		ret;

	ret = 0;
	stp_quote(cmd, env);
	stp_cmd_finish(cmd, env);
	*lex = init_lex();
	make_lex(*lex, *cmd);
	if ((ret = check_syntax(*lex)))
	{
		free_lex(*lex);
		return (ret);
	}
	stp_tilde(*lex, env);
	check_star_inlex(*lex, env);
	remove_quote(*lex, env);
	remove_bslash(*lex, env);
	return (ret);
}
