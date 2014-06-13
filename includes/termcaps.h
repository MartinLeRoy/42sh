/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 17:09:24 by rabid-on          #+#    #+#             */
/*   Updated: 2014/03/27 17:58:34 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H

# include <termios.h>
# include <termcap.h>

# define KEY	key[1] == 0 && key[2] == 0 && key[3] == 0
# define KEY2	key[6] == 0 && key[7] == 0
# define UP		key[0] == 27 && key[1] == 91 && key[2] == 65 && key[3] == 0
# define DOWN	key[0] == 27 && key[1] == 91 && key[2] == 66 && key[3] == 0
# define RIGHT	key[0] == 27 && key[1] == 91 && key[2] == 67 && key[3] == 0
# define LEFT	key[0] == 27 && key[1] == 91 && key[2] == 68 && key[3] == 0
# define RETURN	key[0] == 10 && KEY
# define DEL	key[0] == 127 && KEY
# define DEL2	key[0] == 27 && key[1] == 91 && key[2] == 51 && key[3] == 126
# define HOME	key[0] == 27 && key[1] == 91 && key[2] == 72 && key[3] == 0
# define END	key[0] == 27 && key[1] == 91 && key[2] == 70 && key[3] == 0
# define OPT	key[0] == 27 && key[1] == 91 && key[2] == 49 && key[3] == 59
# define OPTL	OPT && key[4] == 57 && key[5] == 68 && KEY2
# define OPTR	OPT && key[4] == 57 && key[5] == 67 && KEY2
# define OPTU	OPT && key[4] == 57 && key[5] == 65 && KEY2
# define OPTD	OPT && key[4] == 57 && key[5] == 66 && KEY2
# define CTRLD	key[0] == 4 && KEY
# define TAB	key[0] == 9 && KEY
# define CTRLC	key[0] == 3 && KEY

# include "struct.h"

int				ft_auto_check_last_cmd(char *cmd);
int				check_what_file(t_auto *autocomp);
t_auto			*autocomp_prog(t_auto *autocomp, char *cmd);
void			free_autocomp(t_auto *autocomp);
int				autocom_cmd_file_hard(char *cmd, t_auto *autocomp);
int				autocom_cmd_file_simple(char *cmd, t_auto *autocomp);
void			ft_auto_init_data(char *cmd, t_auto *aut);
int				find_file_simple(t_auto *autocomp);
int				find_file(char *open, t_auto *autocomp);
int				find_file3(t_auto *autocomp);
void			add_to_list(t_auto *autocomp, char *tmp);
int				find_cmd(t_auto	*file, int token, int i);
int				ft_is_separation(int c);
int				auto_comp_check5(char *s1, char *dname);
int				auto_comp_check1(char *s1, char *s2);
int				auto_comp_check2(char *s1, char *s2);
t_auto			*ft_auto_init(void);
void			free_list_auto(t_auto *file);
t_line			*do_tab(t_line *line, int flag);

t_term			init_term(int flag);
void			restore_env(int flag);
void			forty_two_sh(t_line *line, char ***env);
char			*get_cmd(t_line *line, int flag);
t_line			*move_cursor(char *key, t_line *line);
void			put_cmd(t_line *line, int flag);
t_line			*move_word(char *key, t_line *line, int flag);
t_line			*add_char(t_line *line, char c, int flag);
t_line			*del_char(char *key, t_line *line, int flag);
t_line			*prev_cmd(char *key, t_line *line, int flag);
t_line			*add_history(t_line *line);
t_line			*init_line(t_line *line, char **env);
int				tputchar(int c);
t_line			*init_line2(t_line *line, char *name);
void			free_line(t_line *line);
void			free_hist(t_hist *hist);
t_line			*check_size(t_line *line, char *key);
t_line			*move_line(char *key, t_line *line);
char			*get_entry(char *prompt);
void			catch_signal(void);
t_line			*resize(t_line *line);
char			*singleton_path(char *path);
t_line			*singleton_line(t_line *line);
char			*exit_prompt(char *key, t_line *line, int flag);

#endif
