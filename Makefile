# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teppei <teppei@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 12:46:40 by teppei            #+#    #+#              #
#    Updated: 2024/06/30 02:00:12 by teppei           ###   ########.fr        #
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
						sort_infos.c \
						print_align.c \
						debugger/print_args.c \

OBJDIR		=	obj
OBJS		=	$(SRCS:%.c=$(OBJDIR)/%.o)
HEAD		=	./incs
INCS		=	-I./incs
LINK		=	-L./libft
LIBS		=	-lft
L_FT		=	libft/libft.a

DEBUGGER_DIR = obj/debugger

all: $(OBJDIR) ${DEBUGGER_DIR} $(NAME)

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

test: all
	@bash ./tests/unit_tests/run_all_tests.sh

test-%: all
	@bash ./tests/unit_tests/${@:test-%=%}.sh

.PHONY: all clean fclean re cl run test test-%
