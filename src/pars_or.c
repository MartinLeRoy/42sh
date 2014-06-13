/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 20:51:10 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/26 16:46:46 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parseur.h"
#include "lexer.h"

static t_lexer		*add_or_ncmd(t_lexer *node, t_parse *tree)
{
	char		**tab;
	t_job		*last_job;

	if (node->next->type == CMD)
		tab = ft_strsplitspace(node->next->str);
	else
		tab = ft_strsplit(node->next->str, '\0');
	last_job = find_last_job(tree);
	if (!is_job_free(last_job))
	{
		last_job->next = init_job();
		last_job->next->prev = last_job;
		last_job = last_job->next;
	}
	last_job->or_inst = init_inst(NULL);
	last_job->or_inst->arg = tab;
	return (node->next->next);
}

static t_lexer		*add_or_alone(t_lexer *node, t_parse *tree)
{
	t_job		*last_job;

	last_job = find_last_job(tree);
	if (!is_job_free(last_job))
	{
		last_job->next = init_job();
		last_job->next->prev = last_job;
		last_job = last_job->next;
	}
	return (node->next);
}

t_lexer				*add_or(t_lexer *node, t_parse *tree)
{
	t_lexer		*ret;

	if (node->next && (node->next->type >= 0 && node->next->type < 4))
		ret = add_or_ncmd(node, tree);
	else
		ret = add_or_alone(node, tree);
	return (ret);
}

int					check_or(t_lexer *node)
{
	if (node->type == OR)
		return (1);
	return (0);
}
