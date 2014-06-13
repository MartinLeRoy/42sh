/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/26 19:09:02 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/27 20:41:16 by dcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "parseur.h"
#include "forty_two_sh.h"

static void		cd_managepwd(char ***env)
{
	char	*buf;
	char	*old;

	buf = NULL;
	buf = getcwd(buf, 0);
	old = sh_getenv("PWD", *env);
	ft_setenv("PWD", buf, 1, env);
	ft_setenv("OLDPWD", old, 1, env);
	free(buf);
	free(old);
}

static void		cd_print_error(char *name, int error)
{
	if (error == 1)
		write(2, "cd: no such file or directory: ", 31);
	else if (error == 2)
		write(2, "cd: permission denied: ", 23);
	ft_putendl_fd(name, 2);
}

static int		cd_is_dirpath(char *dir, char *dir_path)
{
	int			ret;

	ret = 0;
	if (access(dir, F_OK | R_OK) == 0)
		return (0);
	if (access(dir_path, F_OK | R_OK) == 0)
		return (0);
	if ((access(dir, F_OK) == -1) && (access(dir_path, F_OK) == -1))
		return (1);
	if ((access(dir, R_OK) == -1)
		|| (access(dir_path, R_OK) == -1))
		ret = 2;
	return (ret);
}

static int		cd_home(char ***env, char *cd)
{
	char	*newdir;

	if (cd == NULL)
		newdir = sh_getenv("HOME", *env);
	else
		newdir = sh_getenv("OLDPWD", *env);
	chdir(newdir);
	free(newdir);
	cd_managepwd(env);
	return (0);
}

int				sh_cd(char **cd, char ***env)
{
	char	*buf;
	char	*tmp;
	int		error;

	buf = NULL;
	cd++;
	if (!(*cd) || !ft_strcmp(*cd, "-"))
		return (cd_home(env, *cd));
	buf = getcwd(buf, 0);
	tmp = ft_strjoinwsep(buf, *cd, '/');
	free(buf);
	if ((error = cd_is_dirpath(*cd, tmp)) > 0)
	{
		free(tmp);
		cd_print_error(*cd, error);
		return (-1);
	}
	if ((error = chdir(*cd)) != 0)
		error = chdir(tmp);
	if (error == -1)
		ft_putendl("cd: not a directory");
	else
		cd_managepwd(env);
	free(tmp);
	return (0);
}
