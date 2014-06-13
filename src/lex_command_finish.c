/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_command_finish.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 17:18:41 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/27 16:00:19 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "lexer.h"
#include "libft.h"
#include "termcaps.h"

static void			get_next_cmd(char **cmd_ptr)
{
	char	*more;

	more = get_entry("<command> ");
	write(1, "\n", 1);
	cat_cmd(cmd_ptr, &more, 0);
}

static int			stp_cmd_getlastpos(char *cmd)
{
	int		ret;

	ret = (ft_strlen(cmd) - 1);
	while (ret > 0 && ft_isspace(cmd[ret]))
		ret--;
	return (ret);
}

static int			stp_cmd_getfirstpos(char *cmd)
{
	int		ret;

	ret = 0;
	while (cmd[ret] && ft_isspace(cmd[ret]))
		ret++;
	return (ret);
}

int					is_cmd_finish(char *cmd)
{
	int		l;
	int		i;
	int		flag;

	flag = 0;
	l = stp_cmd_getlastpos(cmd);
	i = stp_cmd_getfirstpos(cmd);
	if (l <= 0 || l == i)
		return (0);
	if (cmd[l] == '&' && cmd[l - 1] == '&' && !ft_isbslashed(cmd, l - 1))
		flag++;
	else if (cmd[l] == '|' && cmd[l - 1] == '|' && !ft_isbslashed(cmd, l - 1))
		flag++;
	else if (cmd[l] == '|' && !ft_isbslashed(cmd, l))
		flag++;
	return (flag);
}

void				stp_cmd_finish(char **cmd_ptr, char **env)
{
	char	*cmd;

	cmd = *cmd_ptr;
	if (is_cmd_finish(cmd))
	{
		get_next_cmd(cmd_ptr);
		stp_cmd_finish(cmd_ptr, env);
	}
	stp_quote(cmd_ptr, env);
}
