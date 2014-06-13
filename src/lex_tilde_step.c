/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tilde_step.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/17 13:15:19 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/22 17:47:20 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lexer.h"
#include "forty_two_sh.h"

void			replace_tilde(t_lexer *node, char **env, int pos)
{
	char		*home_ptr;
	char		*new_cmd;

	home_ptr = sh_getenv("HOME", env);
	new_cmd = ft_strnew(ft_strlen(node->str) - 1 + ft_strlen(home_ptr));
	if (new_cmd == NULL)
		ft_exit(PROG, 1);
	ft_strncat(new_cmd, node->str, (pos));
	ft_strcat(new_cmd, home_ptr);
	ft_strcat(new_cmd, node->str + (pos + 1));
	free(node->str);
	free(home_ptr);
	node->str = new_cmd;
}

void			check_tilde(t_lexer *node, char **env)
{
	int			i;
	char		*str;

	i = 0;
	str = node->str;
	while (str[i])
	{
		if (str[i] == '~' && (i == 0 || ft_isspace(str[i - 1])))
			replace_tilde(node, env, i);
		i++;
	}
}

void			stp_tilde(t_lx *lex, char **env)
{
	t_lexer		*browse_lx;

	if (lex == NULL)
		return ;
	browse_lx = lex->first;
	while (browse_lx)
	{
		if (browse_lx->type == CMD)
			check_tilde(browse_lx, env);
		browse_lx = browse_lx->next;
	}
}
