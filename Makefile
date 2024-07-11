# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: waalexan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 15:19:08 by waalexan          #+#    #+#              #
#    Updated: 2024/06/27 15:19:09 by waalexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra

NAME = so_long

SRCS_DIR = srcs
SRCS = $(wildcard $(SRCS_DIR)/*.c)
OBJS = $(SRCS:.c=.o)

LIB_DIR = ./functions
LIB_DIR2 = ./minilibx
LIBFT = $(LIB_DIR)/libft.a
MINILIBX = $(LIB_DIR2)/libmlx_Linux.a

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MINILIBX) -o $(NAME) -lXext -lX11 -lm

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

$(MINILIBX):
	$(MAKE) -C $(LIB_DIR2)

clean:
	$(MAKE) clean -C $(LIB_DIR)
	$(MAKE) clean -C $(LIB_DIR2)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
