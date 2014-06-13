/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_exist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/19 16:30:40 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/25 20:41:16 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "lexer.h"
#include "libft.h"

static int			is_star_list(t_star *test)
{
	if (test == NULL)
		return (1);
	else
		return (0);
	return (0);
}

t_star				*del_first_star(t_lst_star *starz, t_star *to_del)
{
	starz->first = to_del->next;
	starz->first->prev = NULL;
	return (starz->first);
}

static t_star		*del_star_node(t_star *to_del, t_lst_star *starz)
{
	t_star		*ret;

	ret = NULL;
	if (to_del->next == NULL && to_del->prev == NULL)
	{
		starz->first = NULL;
		starz->last = NULL;
	}
	else if (to_del->next == NULL)
	{
		starz->last = to_del->prev;
		starz->last->next = NULL;
	}
	else if (to_del->prev == NULL)
		ret = del_first_star(starz, to_del);
	else
	{
		to_del->prev->next = to_del->next;
		to_del->next->prev = to_del->prev;
		ret = to_del->next;
	}
	free(to_del->add);
	free(to_del);
	return (ret);
}

int					star_exist(t_lst_star *starz, char **env)
{
	t_star		*browse;
	char		*tmp;
	char		*pwd;

	if (starz->after_word == NULL)
		return (0);
	browse = starz->first;
	pwd = sh_getenv("PWD", env);
	while (browse)
	{
		if (access(browse->add, F_OK))
		{
			tmp = ft_strjoinwsep(pwd, browse->add, '/');
			if (access(tmp, F_OK))
				browse = del_star_node(browse, starz);
			else
				browse = browse->next;
			free(tmp);
			tmp = NULL;
		}
		else
			browse = browse->next;
	}
	free(pwd);
	return (is_star_list(starz->first));
}
