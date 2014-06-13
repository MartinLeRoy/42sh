/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 21:19:43 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/26 22:03:40 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_lexer		t_lexer;
typedef struct s_lx			t_lx;

struct				s_lexer
{
	char				*str;
	char				type;
	t_lexer				*next;
	t_lexer				*prev;
};

struct				s_lx
{
	t_lexer				*first;
	t_lexer				*last;
};

typedef struct		s_quote
{
	int					a;
	int					b;
	char				type;
	struct s_quote		*next;
	struct s_quote		*prev;
}					t_quote;

typedef struct		s_lquote
{
	t_quote				*first;
	t_quote				*last;
}					t_lquote;

typedef struct s_star		t_star;
typedef struct s_lst_star	t_lst_star;

struct				s_star
{
	char				*add;
	t_star				*next;
	t_star				*prev;
};

struct				s_lst_star
{
	t_star				*first;
	t_star				*last;
	char				*word;
	char				dir_flag;
	char				*dir;
	char				*word_in_dir;
	char				*after_word;
	int					pos_inword;
	int					pos_str;
	int					start;
	int					end;
};

typedef struct		s_redir
{
	char				*name;
	char				type;
	struct s_redir		*next;
}					t_redir;

typedef struct		s_inst
{
	char				**arg;
	int					fd_in;
	int					fd_out;
	int					fd_err;
	t_redir				*redir;
	struct s_inst		*next;
	struct s_inst		*prev;
}					t_inst;

typedef struct		s_job
{
	t_inst				*inst;
	t_inst				*and_inst;
	t_inst				*or_inst;
	struct s_job		*next;
	struct s_job		*prev;
}					t_job;

typedef struct		s_cmd
{
	t_job				*job;
	struct s_cmd		*next;
}					t_cmd;

typedef struct		s_parse
{
	t_cmd				*cmd;
	char				**path;
	char				***env;
}					t_parse;

typedef int			(*t_check_ptr)(t_lexer *);
typedef t_lexer		*(*t_add_node_ptr)(t_lexer *, t_parse *);

typedef struct		s_check_pars
{
	t_check_ptr			check;
	t_add_node_ptr		add_node;
}					t_check_pars;

typedef struct		s_setenv
{
	char				*name;
	char				*value;
	int					ow;
}					t_setenv;

typedef int		(*t_builtin_ptr)(char **, char ***);

typedef struct		s_builtin
{
	char				*name;
	t_builtin_ptr		fn;
}					t_builtin;

typedef struct		s_export
{
	char				*value;
	char				*value2;
	int					token1;
	int					token2;
}					t_export;

typedef struct termios	t_term;

typedef struct		s_hist
{
	char				*cmd;
	struct s_hist		*next;
	struct s_hist		*prev;
}					t_hist;

typedef struct		s_line
{
	int					col;
	int					fd;
	int					tab_cpt;
	char				*key;
	char				*tab;
	int					pos;
	int					line;
	int					cur;
	char				*cmd;
	char				*prompt;
	char				*path_hist;
	t_hist				*hist;
	int					cpt_hist;
	int					nb_hist;
}					t_line;

typedef struct		s_file
{
	char				*str;
	struct s_file		*next;
	struct s_file		*prev;
}					t_file;

typedef struct		s_auto
{
	t_file				*first;
	t_file				*last;
	int					len;
	char				*start;
	char				*end;
	char				**path;
	char				**tab;
}					t_auto;

#endif
