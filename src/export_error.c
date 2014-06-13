/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaf <jchenaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 07:39:42 by jchenaf           #+#    #+#             */
/*   Updated: 2014/03/27 07:39:47 by jchenaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "exec_sh.h"

void				export_print_error(char *str)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void				export_print_error2(char *str)
{
	if (!ft_isprint(str[1]) && str[0] == '-')
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("\': invalid option", 2);
		ft_putstr_fd("export: usage: export ", 2);
		ft_putendl_fd("[-nf] [name[=value] ...] or export -p", 2);
	}
	else
	{
		ft_putstr_fd("export: ", 2);
		ft_putchar_fd(str[0], 2);
		ft_putchar_fd(str[1], 2);
		ft_putendl_fd(": invalid option", 2);
		ft_putstr_fd("export: usage: export ", 2);
		ft_putendl_fd("[-nf] [name[=value] ...] or export -p", 2);
	}
}

static int			export_count(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	i -= 1;
	return (i);
}

static int			export_isalnum(char *str)
{
	int			i;
	int			j;
	int			check;

	j = -1;
	check = 0;
	i = export_count(str);
	while (i != j)
	{
		if (str[0] != '-')
		{
			if (!ft_isalnum(str[i]))
				check += 1;
		}
		i--;
	}
	if (check > 0 && check != 0)
		return (1);
	else
		return (0);
}

int					check_export_argv(char **req, int i, int j)
{
	if (j == 0)
	{
		if ((export_isalnum(req[i]) == 1) || (ft_isdigit(req[i][0]) == 1))
		{
			j++;
			export_print_error(req[i]);
		}
		if (req[i][0] == '-' && (ft_strcmp(req[i], "-p")
					&& ft_strcmp(req[i], "-n") != 0))
		{
			j++;
			export_print_error2(req[i]);
		}
		if ((ft_strcmp(req[i], "=") == 0) || (check(req[i]) == 0))
		{
			j++;
			export_print_error(req[i]);
		}
	}
	return (j);
}
