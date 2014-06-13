/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_treat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaf <jchenaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 07:40:03 by jchenaf           #+#    #+#             */
/*   Updated: 2014/03/27 07:40:06 by jchenaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "exec_sh.h"

char			*get_first_value(char *str, t_export *data)
{
	char		*new;
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			data->token2 = 1;
			break ;
		}
		i++;
	}
	new = ft_strsub(str, 0, i);
	return (new);
}

int				check(char *str)
{
	int			i;

	i = 0;
	if (ft_strchr(str, '='))
	{
		while (str[i])
		{
			if (str[i] == '=')
				break ;
			i++;
		}
		if (str[i] == '=' && i == 0)
			return (0);
		else
			return (1);
	}
	else
	{
		return (1);
	}
}

void			print_export(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != 0)
	{
		ft_putstr("declare -x ");
		ft_putendl(tab[i]);
		i++;
	}
}

void			ft_sort(char **tab)
{
	int			j;
	int			i;
	char		*tmp;

	i = 0;
	j = 0;
	while (tab[i])
	{
		j = i;
		while (j > 0 && ft_strcmp(tab[j], tab[j - 1]) < 0)
		{
			tmp = tab[j - 1];
			tab[j - 1] = tab[j];
			tab[j] = tmp;
			--j;
		}
		i++;
	}
}

t_export		*init_export(void)
{
	t_export		*new;

	if ((new = (t_export *)malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->value = NULL;
	new->value2 = NULL;
	new->token1 = 0;
	new->token2 = 0;
	return (new);
}
