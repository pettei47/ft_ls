# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teppei <teppei@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/30 17:42:38 by tkitagaw          #+#    #+#              #
#    Updated: 2021/11/06 14:52:31 by teppei           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
CFLGS	=	-Wall -Wextra -Werror -std=c99
LIBS	=	ar -rc
NAME	=	libft.a
SRCS	=	$(shell ls *.c)
OBJS	=	$(SRCS:.c=.o)

.c.o :
	$(CC) $(CFLGS) -c $< -o $@ -I ./

all : $(NAME)

$(NAME) : $(OBJS)
	$(LIBS) $(NAME) $(OBJS)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
