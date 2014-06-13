/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/26 19:14:26 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/27 20:41:22 by dcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "libft.h"
#include "parseur.h"
#include "exec_sh.h"

char	*get_env_arg(char **req)
{
	int		i;
	char	*ret;
	char	*tmp;

	i = 0;
	ret = ft_strnew(0);
	while (req[i])
	{
		tmp = ft_strjoinwsep(ret, req[i], ' ');
		free(ret);
		ret = tmp;
		i++;
	}
	return (ret);
}

int		exec_env_cmd(t_inst *inst, t_parse *tree)
{
	pid_t	ret;
	pid_t	pid;

	ret = 0;
	if ((pid = fork()) == 0)
		exec_cmd(inst, tree);
	else
		waitpid(pid, &ret, WUNTRACED);
	return (ret);
}

int		prep_env_cmd(char **req, char ***env, int flag)
{
	t_parse		*env_tree;
	t_inst		*env_inst;
	char		**null_env;
	char		*arg;
	int			ret;

	ret = 0;
	env_tree = init_tree(env);
	if (flag)
	{
		null_env = (char **)malloc(sizeof(*null_env) * 1);
		null_env[0] = NULL;
		env_tree->env = &null_env;
	}
	arg = get_env_arg(req);
	env_inst = init_inst(arg);
	free(arg);
	ret = exec_env_cmd(env_inst, env_tree);
	free_pars(env_tree);
	free_inst(env_inst);
	if (flag)
		ft_tabfree(&null_env);
	return (ret);
}

int		sh_env(char **req, char ***env)
{
	int				i;
	int				flag;

	flag = 0;
	if (req[1])
	{
		req++;
		if (!ft_strcmp(*req, "-i"))
		{
			req++;
			if (*req == NULL)
				return (0);
			flag++;
		}
		return (prep_env_cmd(req, env, flag));
	}
	else
	{
		i = 0;
		while ((*env)[i])
			ft_putendl((*env)[i++]);
	}
	return (0);
}
