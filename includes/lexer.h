/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/13 14:06:13 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/26 21:22:16 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define PROG "42sh"

# define BUFF_QUOTE 2096
# define BUFF_CMD 2096

# define CMD 0
# define QUOTE_D 1
# define QUOTE_S 2
# define QUOTE_B 3
# define PIPE 4
# define SEP 5
# define OR 6
# define AND 7
# define REDIR_L 8
# define REDIR_R 9
# define APPEND_R 10
# define REDIR_D 11
# define REDIR_ER 12
# define HEREDOC 13

# include "struct.h"

int			is_quote_closed(char *cmd);
void		stp_tilde(t_lx *lex, char **env);
void		stp_dollar(char **cmd, char **env);
int			ft_isbslashed(char *str, int pos);

/*
** LEX_CHECK_SYNTAX
*/
int			check_syntax(t_lx *lex);

/*
** LEX_TILDE_STEP
*/
char		*sh_getenv(char *var, char **env);

/*
** LEX_QUOTE_STEP
*/
void		stp_quote(char **cmd, char **env);

/*
** LEX_QUOTE_STP_INIT_FREE
*/
t_quote		*init_quote(int a, int b, char quote);
t_lquote	*init_lquote(void);
void		free_quote_list(t_lquote *quote_list);

/*
** LEX_GET_ADD_NEXT_QUOTE
*/
void		add_quote_lst(t_lquote *lquote, int a, int b, char quote);
char		*get_more(char quote);

/*
** LEX_COMMAND_FINISH
*/
void		stp_cmd_finish(char **cmd_ptr, char **env);
int			is_cmd_finish(char *cmd);

/*
** LEX_GET_TYPE
*/
char		lex_get_type(char *op);

/*
** LEX_MAKE
*/
void		make_lex(t_lx *lex, char *cmd);

/*
** LEX_FN1
*/
void		add_token(t_lx *lex, t_lexer *token);
t_lexer		*new_token(void);
t_lx		*init_lex(void);

/*
** LEX_BROWSE_QUOTE
*/
int			lex_isquote(char *tolex, int pos, char *cmd);
int			browse_quote(char *ptr, int pos, char *cmd);

/*
** SH_LEXER
*/
int			sh_lexer(t_lx **lex, char **cmd, char **env);
void		free_node_lex(t_lexer *node);
void		free_lex(t_lx *lex);
void		cat_cmd(char **cmd_ptr, char **str, int bsn);

/*
** LEX_REMOVE_BSLASH
*/
void		remove_bslash(t_lx *lex, char **env);

/*
** LEX_REMOVE_QUOTE
*/
void		remove_quote(t_lx *lex, char **env);

/*
** LEX_STAR_STEP
*/
void		check_star_inlex(t_lx *lex, char **env);

/*
** STAR_MAKE_LST
*/
t_lst_star	*get_star(char *cmd, int pos);

/*
** STAR_INIT
*/
t_lst_star	*init_lst_star(char *cmd, int pos);

/*
** STAR_INIT_INT
*/
int			st_get_start(char *str, int star);
int			st_get_end(char *str, int star);
int			st_get_posinword(char *word);

/*
** STAR_ADD_NODE
*/
void		add_star(t_lst_star *starz, t_lexer *node, char **env);

/*
** STAR_EXIST
*/
int			star_exist(t_lst_star *starz, char **env);

#endif
