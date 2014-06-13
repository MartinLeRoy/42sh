/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_fn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/22 17:38:11 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/27 18:01:47 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "forty_two_sh.h"

int					msh_isenv(const char *env, const char *tofind)
{
	int		len;

	len = 0;
	if (ft_strncmp(env, tofind, len = ft_strlen(tofind)) == 0)
	{
		if (env[len] == '=' || (env[len + 1] && env[len + 1] == '='))
			return (1);
		else
			return (0);
	}
	return (0);
}

char				*sh_getenv(char *var, char **env)
{
	char			**tmp;
	char			*value;
	int				len;

	value = NULL;
	tmp = env;
	while (*tmp)
	{
		if ((ft_strnequ(*tmp, var, (len = ft_strlen(var))) == 1))
		{
			if ((*tmp)[len + 1] == '=')
				len++;
			value = ft_strdup((*tmp) + len + 1);
			return (value);
		}
		tmp++;
	}
	return (value);
}

void				check_env(char ***env)
{
	char		*tmp;

	if ((tmp = sh_getenv("PATH", *env)) == NULL)
		ft_setenv("PATH", "/bin", 1, env);
	else
		free(tmp);
	tmp = NULL;
	if ((tmp = sh_getenv("PWD", *env)) == NULL)
	{
		tmp = getcwd(tmp, 0);
		ft_setenv("PWD", tmp, 1, env);
		free(tmp);
	}
	else
		free(tmp);
	tmp = NULL;
	if ((tmp = sh_getenv("OLDPWD", *env)) == NULL)
	{
		tmp = getcwd(tmp, 0);
		ft_setenv("OLDPWD", tmp, 1, env);
		free(tmp);
		tmp = NULL;
	}
	else
		free(tmp);
}

char				*dup_env_init(char *str)
{
	char		*ret;
	char		*ptr;
	int			val;
	char		*val_to_char;

	if (!ft_strncmp(str, "SHLVL=", 6))
	{
		ptr = ft_strchr(str, '=');
		ptr++;
		val = ft_atoi(ptr);
		if (val < 1)
			ft_exit("42sh: SHLVL value incorrect\n", -1);
		val++;
		val_to_char = ft_itoa(val);
		ret = ft_strjoin("SHLVL=", val_to_char);
		free(val_to_char);
		return (ret);
	}
	else
	{
		ret = ft_strdup(str);
		return (ret);
	}
}

char				**sh_envinit(void)
{
	extern char		**environ;
	char			**env;
	int				i;
	int				t;

	i = 0;
	t = 0;
	while (environ[i])
		i++;
	if (i == 0)
		ft_exit("42sh: No environment", -1);
	else
	{
		if ((env = (char **)(malloc(sizeof(char *) * (i + 1)))) == NULL)
			ft_exit("malloc", 1);
		while (t < i)
		{
			env[t] = dup_env_init(environ[t]);
			t++;
		}
		env[t] = '\0';
	}
	ft_setenv("SHELL", "42sh", 1, &env);
	return (env);
}
