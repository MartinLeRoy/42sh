/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaf <jchenaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 07:37:58 by jchenaf           #+#    #+#             */
/*   Updated: 2014/03/27 18:10:29 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <stdlib.h>
#include <dirent.h>
#include "termcaps.h"
#include "libft.h"

int				find_file_simple(t_auto *autocomp)
{
	DIR				*dir;
	struct dirent	*diren;
	int				i;

	i = 0;
	if ((dir = opendir(".")) == NULL)
		return (i);
	while ((diren = readdir(dir)) != NULL)
	{
		if (diren->d_name[0] != '.')
			add_to_list(autocomp, diren->d_name);
		i++;
	}
	closedir(dir);
	return (i);
}

static int		check_strncmp_auto(char *s1, char *dname)
{
	if (ft_strncmp(s1, dname, ft_strlen(s1)) == 0)
		return (1);
	else
		return (0);
}

int				find_file(char *open, t_auto *autocomp)
{
	DIR				*dir;
	struct dirent	*diren;
	int				i;

	i = 0;
	if ((dir = opendir(open)) == NULL)
		return (i);
	while ((diren = readdir(dir)) != NULL)
	{
		if (check_strncmp_auto(autocomp->end, diren->d_name) == 1
				&& diren->d_name[0] != '.')
			add_to_list(autocomp, diren->d_name);
		i++;
	}
	closedir(dir);
	return (i);
}

int				find_file3(t_auto *autocomp)
{
	DIR				*dir;
	struct dirent	*diren;
	int				i;

	i = 0;
	if ((dir = opendir(autocomp->start)) == NULL)
		return (i);
	while ((diren = readdir(dir)) != NULL)
	{
		if (diren->d_name[0] != '.')
			add_to_list(autocomp, diren->d_name);
		i++;
	}
	closedir(dir);
	return (i);
}
