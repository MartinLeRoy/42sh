/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaf <jchenaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 07:39:25 by jchenaf           #+#    #+#             */
/*   Updated: 2014/03/27 07:39:26 by jchenaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "exec_sh.h"
#include "libft.h"

static char			*add_quote_to_double_str(char *s1, char *s2)
{
	char			*new;
	char			*tmp;
	char			*tmp2;

	tmp = ft_strjoin(s1, "\"");
	tmp2 = ft_strjoin(tmp, s2);
	free(tmp);
	new = ft_strjoin(tmp2, "\"");
	free(tmp2);
	return (new);
}

static char			*get_first_value2(char *str)
{
	char			*new;
	int				i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	new = ft_strsub(str, 0, i + 1);
	return (new);
}

static char			*ft_strdup_add_quote(char *str)
{
	char			*s1;
	char			*s2;
	char			*new;

	s1 = get_first_value2(str);
	s2 = ft_strsub(str, ft_strlen(s1), ft_strlen(str) - ft_strlen(s1));
	new = add_quote_to_double_str(s1, s2);
	free(s1);
	free(s2);
	return (new);
}

char				**ft_copy_export(char **tab)
{
	char			**tab_dup;
	int				i;
	int				t;

	t = 0;
	i = 0;
	while (tab[i])
		i++;
	if ((tab_dup = (char **)(malloc(sizeof(char *) * (i + 1)))) == NULL)
		return (NULL);
	while (t < i)
	{
		tab_dup[t] = ft_strdup_add_quote(tab[t]);
		t++;
	}
	tab_dup[t] = NULL;
	return (tab_dup);
}
