/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaf <jchenaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 07:37:23 by jchenaf           #+#    #+#             */
/*   Updated: 2014/03/27 19:32:56 by dcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

static int		auto_check_last(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	i -= 1;
	if (ft_isspace(str[i]))
		return (1);
	else
		return (0);
}

static int		ft_auto_check2(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	while (i > 0)
	{
		if (ft_is_separation(cmd[i]) == 1)
			return (1);
		else
			return (0);
		--i;
	}
	return (0);
}

int				autocom_cmd_file_hard(char *cmd, t_auto *autocomp)
{
	int		size;
	int		len;

	ft_auto_init_data(cmd, autocomp);
	len = autocomp->len;
	size = 0;
	if (len == 1)
		size = find_cmd(autocomp, 1, 0);
	if (len == 2)
		size = check_what_file(autocomp);
	if (size == 0)
	{
		if (ft_auto_check_last_cmd(autocomp->tab[len - 2]) == 1)
			size = find_cmd(autocomp, 1, 0);
		if (size == 0)
			size = check_what_file(autocomp);
	}
	return (size);
}

static int		is_empty_auto(char *str)
{
	int i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int				autocom_cmd_file_simple(char *cmd, t_auto *autocomp)
{
	int		size;

	size = 0;
	if (ft_strlen(cmd) == 0 || is_empty_auto(cmd))
		size = find_cmd(autocomp, 0, 0);
	else if (ft_auto_check_last_cmd(cmd) == 1)
		size = find_cmd(autocomp, 0, 0);
	else if (auto_check_last(cmd) == 1 && ft_auto_check2(cmd) != 1)
		size = find_file_simple(autocomp);
	return (size);
}
