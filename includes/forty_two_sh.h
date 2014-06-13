/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forty_two_sh.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/22 16:03:24 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/26 21:25:55 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORTY_TWO_SH_H
# define FORTY_TWO_SH_H

# include "struct.h"

int		ft_setenv(const char *name, const char *value, int ow, char ***env);
char	**sh_envinit(void);
char	*sh_getenv(char *var, char **env);
int		msh_isenv(const char *env, const char *tofind);
void	check_env(char ***env);
char	***single_env(char ***env);

#endif
