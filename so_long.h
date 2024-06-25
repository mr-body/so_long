#ifndef SO_LONG_H
#define SO_LONG_H

#include "minilibx/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
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
	int  value;
} t_map;


typedef struct s_data {
    void *mlx;
    void *win;
    void *textures[5];
    void *img;
    int win_width;
    int win_heigth;
    int img_x;
    int img_y;
    t_map *map;
} t_data;

#endif
