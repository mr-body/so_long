NAME = game

$(NAME):
	cc *.c -L./minilibx -lmlx_Linux -lXext -lX11 -lm -o ${NAME}
fclean:
	rm ${NAME}

re: fclean ${NAME}
