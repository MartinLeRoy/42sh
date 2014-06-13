/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 22:37:41 by rabid-on          #+#    #+#             */
/*   Updated: 2014/03/27 17:48:57 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "termcaps.h"

t_line	*get_comp(t_line *line, char *str)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	i = ft_strlen(line->cmd);
	if (!line->tab)
		line->tab = ft_strdup(line->cmd);
	while (i >= 0 && (!ft_isspace(line->cmd[i]) && line->cmd[i] != '/'))
		i--;
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	while (j <= i && line->cmd[j])
	{
		tmp[j] = line->cmd[j];
		j++;
	}
	tmp[j] = '\0';
	free(line->cmd);
	line->cmd = ft_strjoin(tmp, str);
	free(tmp);
	return (line);
}

t_line	*do_comp(t_line *line, t_auto *comp, int flag)
{
	t_file	*list;
	int		i;

	i = 0;
	list = comp->first;
	while (list && i++ < line->tab_cpt)
		list = list->next;
	if (!list)
		return (line);
	line = get_comp(line, list->str);
	line->col = ft_strlen(line->cmd) + ft_strlen(line->prompt);
	line->pos = line->col;
	line->tab_cpt++;
	put_cmd(line, flag);
	return (line);
}

t_line	*put_tab(t_line *line, t_auto *comp)
{
	t_file	*list;
	int		i;

	i = 0;
	list = comp->first;
	if (line->tab)
	{
		free(line->tab);
		line->tab = NULL;
	}
	line->tab_cpt = 0;
	ft_putchar('\n');
	while (list)
	{
		ft_putendl(list->str);
		i++;
		list = list->next;
	}
	while (i-- + 1)
		tputs(tgetstr("up", NULL), 1, tputchar);
	i = 0;
	while (i++ < line->col)
		tputs(tgetstr("nd", NULL), 1, tputchar);
	return (line);
}

t_line	*do_tab(t_line	*line, int flag)
{
	t_auto	*comp;
	char	*key;

	key = ft_strdup(line->key);
	comp = ft_auto_init();
	if (line->tab && TAB)
		comp = autocomp_prog(comp, line->tab);
	else
		comp = autocomp_prog(comp, line->cmd);
	if (TAB && comp->first)
		line = do_comp(line, comp, flag);
	else if (comp->first)
		line = put_tab(line, comp);
	free(key);
	free_list_auto(comp);
	return (line);
}
