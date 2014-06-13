# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/03/24 16:08:41 by mle-roy           #+#    #+#              #
#    Updated: 2014/03/27 20:35:56 by dcohen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=42sh
VERSION=1.1.1
CFLAGS=-Wall -Werror -Wextra -g
INCLUDES=-I ./libft/includes -I ./includes
LIBS=-L ./libft -l ft -L /usr/lib -ltermcap
SRCDIR= ./src/

SRC=$(SRCDIR)builtin_cd.c \
	$(SRCDIR)builtin_echo.c \
	$(SRCDIR)builtin_env.c \
	$(SRCDIR)builtin_exit.c \
	$(SRCDIR)builtin_export.c \
	$(SRCDIR)builtin_history.c \
	$(SRCDIR)builtin_setenv.c \
	$(SRCDIR)builtin_unsetenv.c \
	$(SRCDIR)builtin_extra.c \
	$(SRCDIR)check_size.c \
	$(SRCDIR)edit_cmd.c \
	$(SRCDIR)exec_cmd.c \
	$(SRCDIR)exec_job.c \
	$(SRCDIR)exec_pipe.c \
	$(SRCDIR)exec_redir.c \
	$(SRCDIR)export_copy.c \
	$(SRCDIR)export_error.c \
	$(SRCDIR)export_treat.c \
	$(SRCDIR)init_autocomp.c \
	$(SRCDIR)ft_isbslashed.c \
	$(SRCDIR)ft_setenv.c \
	$(SRCDIR)free_line.c \
	$(SRCDIR)get_cmd.c \
	$(SRCDIR)history.c \
	$(SRCDIR)init_line.c \
	$(SRCDIR)init_term.c \
	$(SRCDIR)key_cmd.c \
	$(SRCDIR)lex_browse_quote.c \
	$(SRCDIR)lex_check_syntax.c \
	$(SRCDIR)lex_command_finish.c \
	$(SRCDIR)lex_fn1.c \
	$(SRCDIR)lex_get_add_next_quote.c \
	$(SRCDIR)lex_get_type.c \
	$(SRCDIR)lex_make.c \
	$(SRCDIR)lex_quote_step.c \
	$(SRCDIR)lex_quote_stp_init_free.c \
	$(SRCDIR)lex_remove_bslash.c \
	$(SRCDIR)lex_remove_quote.c \
	$(SRCDIR)lex_star_step.c \
	$(SRCDIR)lex_tilde_step.c \
	$(SRCDIR)main.c \
	$(SRCDIR)move_cursor.c \
	$(SRCDIR)move_line.c \
	$(SRCDIR)move_tab.c \
	$(SRCDIR)move_word.c \
	$(SRCDIR)pars_and.c \
	$(SRCDIR)pars_check.c \
	$(SRCDIR)pars_free.c \
	$(SRCDIR)pars_heredoc.c \
	$(SRCDIR)pars_heredoc_before.c \
	$(SRCDIR)pars_heredoc_new_inst.c \
	$(SRCDIR)pars_init.c \
	$(SRCDIR)pars_inst.c \
	$(SRCDIR)pars_new_cmd.c \
	$(SRCDIR)pars_or.c \
	$(SRCDIR)pars_pipe.c \
	$(SRCDIR)pars_quote.c \
	$(SRCDIR)pars_redir.c \
	$(SRCDIR)pars_redir_new_inst.c \
	$(SRCDIR)pars_search_tree.c \
	$(SRCDIR)sh_builtin.c \
	$(SRCDIR)sh_env_fn.c \
	$(SRCDIR)sh_exec.c \
	$(SRCDIR)sh_lexer.c \
	$(SRCDIR)sh_parsing.c \
	$(SRCDIR)signal.c \
	$(SRCDIR)singleton.c \
	$(SRCDIR)star_add_node.c \
	$(SRCDIR)star_exist.c \
	$(SRCDIR)star_init.c \
	$(SRCDIR)star_init_int.c \
	$(SRCDIR)star_make_lst.c \
	$(SRCDIR)autocomp.c \
	$(SRCDIR)autocomp1.c \
	$(SRCDIR)autocomp2.c \
	$(SRCDIR)autocomp3.c \
	$(SRCDIR)autocomp4.c \
	$(SRCDIR)autocomp5.c \

OBJ= $(SRC:.c=.o)

all: build $(NAME) finish

build:
	@($(MAKE) -C ./libft)

$(NAME): $(OBJ) ./libft/libft.a
	gcc $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBS)

%.o: %.c
	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@(rm -rf $(OBJ))

fclean: clean
	@(rm -rf $(NAME))
	@($(MAKE) -C ./libft fclean)

re: fclean all

v:
	@(echo "version: $(VERSION)")

finish:
	@(echo "[\033[32m$(NAME)\033[00m]")

.PHONY: all build clean fclean re v

