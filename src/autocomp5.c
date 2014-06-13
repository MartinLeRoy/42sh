/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaf <jchenaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 07:38:26 by jchenaf           #+#    #+#             */
/*   Updated: 2014/03/27 07:38:28 by jchenaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <stdlib.h>
#include <dirent.h>
#include "termcaps.h"
#include "libft.h"

int				ft_is_separation(int c)
{
	if (c == ';' || c == '&' || c == '|')
		return (1);
	else
		return (0);
}

int				auto_comp_check5(char *s1, char *dname)
{
	if (ft_strncmp(s1, dname, ft_strlen(s1)) == 0)
		return (1);
	else
		return (0);
}

int				auto_comp_check1(char *s1, char *s2)
{
	if (s1[0] != '\0' && ft_strlen(s1) != ft_strlen(s2))
		return (1);
	else
		return (0);
}

int				auto_comp_check2(char *s1, char *s2)
{
	if (s1[0] != '\0' && ft_strlen(s1) == ft_strlen(s2))
		return (1);
	else
		return (0);
}
