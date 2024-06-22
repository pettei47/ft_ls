# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teppei <teppei@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 12:46:40 by teppei            #+#    #+#              #
#    Updated: 2024/06/22 17:37:41 by teppei           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_ls
CC			=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g
SRCDIR	=	src
SRCS		:=	main.c
OBJDIR		=	obj
OBJS		=	$(SRCS:%.c=$(OBJDIR)/%.o)
HEAD		=	./incs
INCS		=	-I./incs
LINK		=	-L./libft
LIBS		=	-lft
L_FT		=	libft/libft.a

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir $(OBJDIR)

$(NAME): $(OBJS) $(L_FT)
	$(CC) -o $@ $^ $(LINK) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(L_FT):
	@make -C libft

clean:
	rm -f $(OBJS) $(MOBJS) */*.gch
	rm -rf *.dSYM
fclean: clean
	rm -f $(NAME)

re: fclean all
cl: all clean

run: all
	./$(NAME)

.PHONY: all clean fclean re cl run
