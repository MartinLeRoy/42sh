/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaf <jchenaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 07:38:54 by jchenaf           #+#    #+#             */
/*   Updated: 2014/03/27 20:41:25 by dcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "exec_sh.h"
#include "libft.h"
#include "forty_two_sh.h"

static t_export		*treat_export(char *str, t_export *data)
{
	int			len;
	int			len2;

	data->token1 = 1;
	data->value = get_first_value(str, data);
	if (data->token2 == 1)
	{
		len = ft_strlen(data->value) + 1;
		len2 = ft_strlen(str);
		data->value2 = ft_strsub(str, len, len2);
	}
	return (data);
}

static void			add_export(t_export *data, char ***env)
{
	if (data->token1 == 1 && data->token2 == 0)
		ft_setenv(data->value, "", 1, env);
	else if (data->token1 == 1 && data->token2 == 1)
		ft_setenv(data->value, data->value2, 1, env);
}

static void			export_argv(char **req, char ***env)
{
	t_export	*data;
	int			i;
	int			j;

	i = 1;
	j = 0;
	while (req[i])
	{
		data = init_export();
		if ((check_export_argv(req, i, j)) != 0)
			j++;
		if (req[i][0] != '-' && j == 0)
			data = treat_export(req[i], data);
		if (data->token1 == 1 && j == 0)
			add_export(data, env);
		free(data->value);
		free(data->value2);
		free(data);
		i++;
	}
}

static void			export_simple(char ***env)
{
	char		**export;

	export = ft_copy_export(*env);
	ft_sort(export);
	print_export(export);
	ft_tabfree(&export);
}

int					sh_export(char **req, char ***env)
{
	if (!req[2] && req[1] && (ft_strcmp(req[1], "-n")
				&& ft_strcmp(req[1], "-p")) == 0)
		export_simple(env);
	if (req[1])
		export_argv(req, env);
	else
		export_simple(env);
	return (0);
}
