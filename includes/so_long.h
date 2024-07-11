/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:05:09 by waalexan          #+#    #+#             */
/*   Updated: 2024/07/11 14:34:45 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx/mlx.h"
# include "../functions/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# define SIZE_Q 30

typedef struct s_map{
	void	*img;
	char	value;
	int		pos_x;
	int		pos_y;
}	t_map;

typedef struct s_staff{
	void	*img;
	char	value;
	int		pos_x;
	int		pos_y;
}	t_staff;

typedef struct s_data {
	void	*mlx;
	void	*win;
	void	*img;
	int		win_width;
	int		passo;
	int		win_heigth;
	int		img_x;
	int		img_y;
	int		coin;
	int		score;
	t_map	*map;
	t_staff	*staff;
}	t_data;

t_map	*create_map(int fd, t_data *data);
int		on_keypress(int keysym, t_data *data);
int		on_destroy(t_data *data);
int		validar_map(char *path, t_data *data);
void	render_map(t_data *data, int time);
int		timer(t_data *data);
void	display(int fd, t_data *data);
void	verif_size(t_data *data, int width, int heigth);

#endif
