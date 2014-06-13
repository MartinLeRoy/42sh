/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaf <jchenaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 07:36:58 by jchenaf           #+#    #+#             */
/*   Updated: 2014/03/27 19:33:15 by dcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "forty_two_sh.h"
#include "termcaps.h"

int					ft_auto_check_last_cmd(char *str)
{
	int			i;

	i = 0;
	while (str[i])
		i++;
	i--;
	while (i >= 0 && ft_isspace(str[i]))
		i--;
	if (ft_is_separation(str[i]) == 1)
		return (1);
	return (0);
}

int					check_what_file(t_auto *autocomp)
{
	int			size;

	size = 0;
	if (auto_comp_check2(autocomp->start, autocomp->end) == 1)
		size = find_file(".", autocomp);
	else if (auto_comp_check1(autocomp->end, autocomp->start))
		size = find_file(autocomp->start, autocomp);
	else if (autocomp->end[0] == '\0')
		size = find_file3(autocomp);
	else
		size = find_file_simple(autocomp);
	return (size);
}

static void			autocom_start(char *cmd, t_auto *autocomp)
{
	int			size;

	size = 0;
	size = autocom_cmd_file_simple(cmd, autocomp);
	if (size == 0)
		size = autocom_cmd_file_hard(cmd, autocomp);
}

static char			**init_env_auto(void)
{
	char		***env;
	char		*tmp;
	char		**path;

	env = single_env(NULL);
	tmp = sh_getenv("PATH", *env);
	path = ft_strsplit(tmp, ':');
	free(tmp);
	return (path);
}

t_auto				*autocomp_prog(t_auto *autocomp, char *cmd)
{
	autocomp->path = init_env_auto();
	autocom_start(cmd, autocomp);
	return (autocomp);
}
