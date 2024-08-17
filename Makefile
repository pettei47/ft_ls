# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teppei <teppei@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 12:46:40 by teppei            #+#    #+#              #
#    Updated: 2024/08/17 18:07:25 by teppei           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_ls
CC			=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g
SRCDIR	=	src
SRCS		:=	main.c \
						parse_args.c \
						sort_paths.c \
						exec_ls.c \
						exec_ls_files.c \
						get_file_stat.c \
						get_file_infos.c \
						sort_infos.c \
						print_file_info.c \
						print_align.c \
						free.c \
						debugger/print_args.c \

OBJDIR		=	obj
OBJS		=	$(SRCS:%.c=$(OBJDIR)/%.o)
HEAD		=	./incs
INCS		=	-I./incs
LINK		=	-L./libft
LIBS		=	-lft
L_FT		=	libft/libft.a

DEBUGGER_DIR = obj/debugger

TEST_OUTOUT_DIR = tests/outputs
TEST_LOG_DIR = tests/logs
TEST_EXPECTS_DIR = tests/expects

all: $(OBJDIR) ${DEBUGGER_DIR} $(NAME)

ci: $(OBJDIR) ${DEBUGGER_DIR}
	cd ${SRCDIR} && mv sort_infos.c sort_infos.c.bak
	cd ${SRCDIR} && mv sort_infos_for_ci.c sort_infos.c
	@make fclean
	@make test

revert_ci_src:
	cd ${SRCDIR} && mv sort_infos.c sort_infos_for_ci.c
	cd ${SRCDIR} && mv sort_infos.c.bak sort_infos.c
	touch ${SRCDIR}/sort_infos.c

$(OBJDIR):
	mkdir $(OBJDIR)

$(DEBUGGER_DIR):
	mkdir $(DEBUGGER_DIR)

$(NAME): $(OBJS) $(L_FT)
	$(CC) -o $@ $^ $(LINK) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(L_FT):
	@make -C libft

clean:
	@make clean -C libft
	rm -f $(OBJS) */*.gch
	rm -rf *.dSYM
fclean: clean
	@make fclean -C libft
	rm -f $(NAME)

re: fclean all
cl: all clean

run: all
	./$(NAME)

test: all $(TEST_OUTOUT_DIR) $(TEST_LOG_DIR) $(TEST_EXPECTS_DIR)
	@bash ./tests/unit_tests/run_all_tests.sh

test-%: all $(TEST_OUTOUT_DIR) $(TEST_LOG_DIR) $(TEST_EXPECTS_DIR)
	@bash ./tests/unit_tests/${@:test-%=%}.sh

$(TEST_OUTOUT_DIR):
	@mkdir $(TEST_OUTOUT_DIR)

$(TEST_LOG_DIR):
	@mkdir $(TEST_LOG_DIR)

$(TEST_EXPECTS_DIR):
	@mkdir $(TEST_EXPECTS_DIR)

.PHONY: all ci revert_ci_src clean fclean re cl run test test-%
