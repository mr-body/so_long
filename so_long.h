/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:06:44 by waalexan          #+#    #+#             */
/*   Updated: 2024/07/21 18:06:45 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
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

typedef struct s_soldier{
	void	*img;
	char	soldier;
	int		pos_x;
	char	*shadow;
	int		shadow_inter;
	int		pos_y;
}	t_soldier;

typedef struct s_cadete{
	void	*img;
	char	*img_old;
	char	soldier;
	char	direction;
	int		pos_x;
	int		pos_y;
	int		pass;
}	t_cadete;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	int			coin;
	int			score;
	int			end;
	t_map		*map;
	t_soldier	soldier;
	t_cadete	cadete;
}	t_data;

t_map	*create_map(int fd, t_data *data);

char	*push_image(char value, t_data *data);
char	*animation(t_data *data);
char	**matriz(t_data *data);

int		validate_map(char *file, t_data *data);
int		on_destroy(t_data *data);
int		on_keypress(int keysym, t_data *data);
int		validate_lines(int fd, t_data *data);
int		ft_render_soldier(int keysym, t_data *data);
int		true_way(char **map, char c, t_data *data);
int		valdate_ext(char *ext);

void	ft_free_valid(t_data *data, char **map);
void	free_matriz(char **matriz, int height);
void	ft_free_width_error(t_data *data);
void	ft_free_path_error(t_data *data);
void	ft_verif_arg(int ac, t_data *data);
void	flood_fill(char **map, int x, int y, int *flg);

void	ft_close_game(t_data *data);
void	ft_pos_sprites(int type, int x, int y, t_data *data);
void	render_map(t_data *data, int time);
void	ft_verific(char value);
void	ft_print_map(t_data *data);
void	ft_free(t_data *data);
void	set_derection(int keysym, t_data *data);
void	display(int fd, t_data *data);

#endif
