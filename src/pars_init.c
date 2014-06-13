/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 21:04:07 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/19 21:07:06 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lexer.h"
#include "parseur.h"

t_redir			*init_redir(char *name, char type)
{
	t_redir		*new;

	if ((new = (t_redir *)malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->name = ft_strdup(name);
	new->type = type;
	new->next = NULL;
	return (new);
}

t_inst			*init_inst(char *str)
{
	t_inst	*new;

	if ((new = (t_inst *)malloc(sizeof(*new))) == NULL)
		return (NULL);
	if (str != NULL)
		new->arg = ft_strsplitspace(str);
	else
		new->arg = NULL;
	new->fd_in = 0;
	new->fd_out = 1;
	new->fd_err = 2;
	new->redir = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_job			*init_job(void)
{
	t_job	*new;

	if ((new = (t_job *)malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->inst = NULL;
	new->and_inst = NULL;
	new->or_inst = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_cmd			*init_cmd(void)
{
	t_cmd	*new;

	if ((new = (t_cmd *)malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->job = NULL;
	new->next = NULL;
	return (new);
}

t_parse			*init_tree(char ***env)
{
	t_parse		*new;
	char		*path;

	if ((new = (t_parse *)malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->cmd = NULL;
	new->env = env;
	path = sh_getenv("PATH", *env);
	new->path = ft_strsplit(path, ':');
	free(path);
	return (new);
}
