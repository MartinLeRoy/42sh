/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/22 16:10:54 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/26 23:51:39 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_SH_H
# define EXEC_SH_H

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define REDIR_L 8
# define REDIR_R 9
# define APPEND_R 10
# define REDIR_D 11
# define REDIR_ER 12
# define HEREDOC 13

# include "parseur.h"
# include "struct.h"

void		exec_job(t_cmd *cmd, t_parse *tree);
void		ft_dup2(int old_fd, int new_fd);
int			is_inst_alone(t_inst *inst);
void		exec_pipe(t_inst *inst, t_parse *tree);
void		add_redir_to_inst(t_inst *inst, t_redir *redir);
int			exec_cmd(t_inst *inst, t_parse *tree);

int			check_builtin(char **arg, char ***env);
int			check_builtin_before(t_cmd *cmd, t_parse *tree);

int			sh_exec(t_parse *tree);
int			sh_cd(char **cd, char ***env);
int			sh_env(char **req, char ***env);
int			sh_setenv(char **req, char ***env);
int			sh_unsetenv(char **req, char ***env);
int			sh_echo(char **req, char ***env);
int			sh_exit(char **req, char ***env);
int			sh_history(char **request, char ***env);
int			sh_export(char **req, char ***env);
int			sh_help(char **req, char ***env);
int			sh_script(char **req, char ***env);
int			sh_exclam(char **req, char ***env);
void		sh_treat_command(char **cmd, char ***env);

t_export	*init_export(void);
void		ft_sort(char **tab);
void		print_export(char **tab);
int			check(char *str);
char		*get_first_value(char *str, t_export *data);
char		**ft_copy_export(char **tab);
int			check_export_argv(char **req, int i, int j);
void		export_print_error2(char *str);
void		export_print_error(char *str);

#endif
