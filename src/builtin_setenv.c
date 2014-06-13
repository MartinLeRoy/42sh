/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/26 19:22:18 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/27 20:41:36 by dcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "forty_two_sh.h"

static int				setenv_ow(char c)
{
	if (c == '0')
		return (0);
	else
		return (1);
}

static int				treat_envmod(char **req, t_setenv *new)
{
	char			*p;

	if (req[0][0] == '-')
	{
		new->ow = setenv_ow(req[0][1]);
		req++;
		if (*req == NULL)
			return (0);
	}
	if ((p = ft_strchr(*req, '=')) != NULL)
	{
		new->name = ft_strndup(*req, (p - *req));
		new->value = ft_strdup(p + 1);
	}
	else
	{
		new->name = ft_strdup(*req);
		req++;
		if (*req)
			new->value = ft_strdup(*req);
		else
			new->value = ft_strnew(0);
	}
	return (1);
}

static t_setenv			*init_tsetenv(void)
{
	t_setenv		*new;

	if ((new = (t_setenv *)malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->ow = 1;
	new->name = NULL;
	new->value = NULL;
	return (new);
}

static void				free_tsetenv(t_setenv *new)
{
	free(new->name);
	if (new->value)
		free(new->value);
	free(new);
}

int						sh_setenv(char **req, char ***env)
{
	t_setenv	*new;
	char		**env_mod;

	env_mod = req;
	env_mod++;
	if (*env_mod == NULL)
		return (0);
	new = init_tsetenv();
	if (treat_envmod(env_mod, new))
	{
		if (ft_setenv(new->name, new->value, new->ow, env) == -1)
		{
			free_tsetenv(new);
			return (-1);
		}
	}
	free_tsetenv(new);
	return (0);
}
