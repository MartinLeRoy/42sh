/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/22 17:00:00 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/26 18:28:58 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "exec_sh.h"
#include "parseur.h"

static int			access_error(char *name, char **path)
{
	char	*tmp;

	if (access(name, F_OK) == 0 && access(name, X_OK) != 0)
	{
		write(2, name, ft_strlen(name));
		write(2, ": you don't have the rights to execute\n", 39);
		return (-1);
	}
	while (*path)
	{
		tmp = ft_strjoinwsep(*path, name, '/');
		if (access(tmp, F_OK) == 0 && access(tmp, X_OK) != 0)
		{
			write(2, name, ft_strlen(name));
			write(2, ": you don't have the rights to execute\n", 39);
			free(tmp);
			return (-1);
		}
		free(tmp);
		path++;
	}
	write(2, name, ft_strlen(name));
	write(2, ": command not found\n", 20);
	return (-1);
}

static int			check_access(char *path)
{
	if (access(path, F_OK | X_OK) == 0)
		return (1);
	else
		return (0);
}

static int			sh_do_command(char *path, char **req, char **env)
{
	if (execve(path, req, env) == -1)
		exit(-1);
	exit(0);
}

int					exec_cmd(t_inst *inst, t_parse *tree)
{
	char	*tmp;
	char	**path;
	int		ret;

	path = tree->path;
	if ((ret = check_builtin(inst->arg, tree->env)) == 1)
	{
		if (check_access(*(inst->arg)))
			sh_do_command(*(inst->arg), inst->arg, *(tree->env));
		while (*path)
		{
			tmp = ft_strjoinwsep(*path, *(inst->arg), '/');
			if (check_access(tmp))
				sh_do_command(tmp, inst->arg, *(tree->env));
			free(tmp);
			path++;
		}
		exit(access_error(*(inst->arg), tree->path));
	}
	exit(ret);
}
