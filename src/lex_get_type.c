/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_get_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 17:37:10 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/21 17:39:16 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

static char			get_type_two(char *op)
{
	if (!ft_strncmp(op, "<<", 2))
		return (HEREDOC);
	else if (!ft_strncmp(op, ">>", 2))
		return (APPEND_R);
	else if (!ft_strncmp(op, "&>", 2))
		return (REDIR_D);
	else if (!ft_strncmp(op, "2>", 2))
		return (REDIR_ER);
	else if (!ft_strncmp(op, "1>", 2))
		return (REDIR_R);
	else if (!ft_strncmp(op, "||", 2))
		return (OR);
	else if (!ft_strncmp(op, "&&", 2))
		return (AND);
	return (0);
}

char				lex_get_type(char *op)
{
	char	ret;

	if ((ret = get_type_two(op)) > 0)
		return (ret);
	else if (*op == '<')
		return (REDIR_L);
	else if (*op == '>')
		return (REDIR_R);
	else if (*op == '|')
		return (PIPE);
	else if (*op == ';')
		return (SEP);
	else if (*op == '\"')
		return (QUOTE_D);
	else if (*op == '\'')
		return (QUOTE_S);
	else if (*op == '`')
		return (QUOTE_B);
	return (CMD);
}
