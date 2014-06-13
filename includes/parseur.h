/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 18:36:24 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/26 21:24:05 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEUR_H
# define PARSEUR_H

# define BUFF_HD 1024

# include "lexer.h"
# include "struct.h"

void		sh_parsing(t_lx *lex, t_parse *tree);

t_parse		*init_tree(char ***env);
t_cmd		*init_cmd(void);
t_job		*init_job(void);
t_inst		*init_inst(char *str);
t_redir		*init_redir(char *name, char type);

int			check_redir(t_lexer *node);
int			check_new_cmd(t_lexer *node);
int			check_inst(t_lexer *node);
int			check_or(t_lexer *node);
int			check_and(t_lexer *node);
int			check_pipe(t_lexer *node);
int			check_quote(t_lexer *node);
int			check_heredoc(t_lexer *node);

t_lexer		*add_redir_tree(t_lexer *node, t_parse *tree);
t_lexer		*add_new_cmd(t_lexer *node, t_parse *tree);
t_lexer		*add_inst(t_lexer *node, t_parse *tree);
t_lexer		*add_or(t_lexer *node, t_parse *tree);
t_lexer		*add_and(t_lexer *node, t_parse *tree);
t_lexer		*add_pipe(t_lexer *node, t_parse *tree);
t_lexer		*add_heredoc(t_lexer *node, t_parse *tree);
t_lexer		*add_quote(t_lexer *node, t_parse *tree);

void		free_pars(t_parse *tree);
void		free_cmd(t_cmd *cmd);
void		free_job(t_job *job);
void		free_inst(t_inst *inst);
void		free_redir(t_redir *redir);

void		add_cmd_tree(t_parse *tree);
void		cat_cmd_pars(t_inst *inst, char **tab, int arg);
void		add_redir(t_inst *inst, char *name, char type);
t_inst		*redir_in_new_inst(t_lexer *node, t_parse *tree, char **tab);
t_inst		*heredoc_new_inst(t_lexer *node, t_parse *tree, char ***heredoc);
t_inst		*heredoc_b4_inst(t_parse *tree, char ***heredoc);
int			check_parsing(t_parse *tree);

t_job		*find_last_job(t_parse *tree);
t_inst		*find_last_inst(t_parse *tree);
int			is_job_free(t_job *job);
int			is_inst_free(t_inst *inst);

void		free_pars(t_parse *tree);
void		free_lex(t_lx *lex);

#endif
