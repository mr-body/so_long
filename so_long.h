#ifndef SO_LONG_H
#define SO_LONG_H

#include "minilibx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define IMG_START_X 0
#define IMG_START_Y 60

#define SIZE_Q 60

typedef struct s_map{
	void *img;
	int	 pos_x;
	int  pos_y;
	char  value;
} t_map;


typedef struct s_data {
    void *mlx;
    void *win;
    void *img;
    int win_width;
    int win_heigth;
    int img_x;
    int img_y;
	int coin;
	int score;
    t_map *map;
} t_data;


int     on_keypress(int keysym, t_data *data);
t_map   *create_map(int fd, t_data *data);
void    display(int fd, t_data *data);
int     on_destroy(t_data *data);
void    render_map(t_data *data);

#endif
