/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/22 16:41:03 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/26 23:51:17 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "exec_sh.h"
#include "parseur.h"

static int			sh_heredoc(char **req, char ***env)
{
	int			i;

	i = 1;
	(void)env;
	while (req[i])
	{
		ft_putendl(req[i]);
		i++;
	}
	return (0);
}

static int			sh_do_builtin(char **req, t_builtin builtin, char ***env)
{
	int		ret;

	ret = builtin.fn(req, env);
	return (ret);
}

t_builtin			*get_builtin(void)
{
	static t_builtin	g_builtin[] =

	{
	{"exit", &sh_exit},
	{"cd", &sh_cd},
	{"env", &sh_env},
	{"setenv", &sh_setenv},
	{"unsetenv", &sh_unsetenv},
	{"echo", &sh_echo},
	{"heredoc_builtin_sh", &sh_heredoc},
	{"history", &sh_history},
	{"export", &sh_export},
	{"help", &sh_help},
	{"42sh", &sh_script},
	{"!", &sh_exclam},
	{NULL, NULL}
	};
	return (g_builtin);
}

int					check_builtin(char **arg, char ***env)
{
	int					i;
	int					ret;
	t_builtin			*g_builtin;

	i = 0;
	g_builtin = get_builtin();
	while (g_builtin[i].name)
	{
		if (ft_strcmp(g_builtin[i].name, *arg) == 0)
		{
			ret = sh_do_builtin(arg, g_builtin[i], env);
			return (ret);
		}
		i++;
	}
	return (1);
}

int					check_builtin_before(t_cmd *cmd, t_parse *tree)
{
	t_job	*job;

	job = cmd->job;
	if (job && job->next)
		return (1);
	if (job && job->inst)
	{
		if (job->inst->next == NULL)
			return (check_builtin(job->inst->arg, tree->env));
		else
			return (1);
	}
	return (1);
}
