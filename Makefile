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

SRCS_DIR = ./
SRCS = ft_create_map.c \
		ft_render_map.c \
		ft_utils.c \
		main.c \
		ft_events.c \
		ft_game_case.c \
		ft_render_soldier.c \
		ft_validate_map.c \
		ft_printer_map.c

OBJS = $(SRCS:.c=.o)


SRCS_BONUS_DIR = srcs_bonus
SRCS_BONUS = ft_create_map.c \
		ft_render_map_bonus.c \
		ft_utils.c \
		main_bonus.c \
		ft_printer_map.c \
		ft_events_bonus.c \
		ft_game_case.c \
		ft_render_soldier.c \
		ft_validate_map.c
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

LIB_DIR = ./libft
LIB_DIR2 = ./minilibx-linux
LIBFT = $(LIB_DIR)/libft.a
MINILIBX = $(LIB_DIR2)/libmlx_Linux.a
VALGRIND = valgrind --leak-check=full

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MINILIBX) -o $(NAME) -lXext -lX11 -lm
run:
	${VALGRIND} ./${NAME} ./maps/map4.ber

bonus: $(OBJS_BONUS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) $(MINILIBX) -o $(NAME) -lXext -lX11 -lm

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

$(MINILIBX):
	$(MAKE) -C $(LIB_DIR2)

clean:
	$(MAKE) fclean -C $(LIB_DIR)
	$(MAKE) clean -C $(LIB_DIR2)
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

git:
	git add .
	git commit -m $(NAME)
	git push

norm:
	norminette ./*.c
	norminette libft

re: fclean all

.PHONY: all clean fclean re
