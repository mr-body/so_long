/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:56:24 by waalexan          #+#    #+#             */
/*   Updated: 2024/07/21 18:24:53 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*push_image(char value, t_data *data)
{
	if (data->end != 1)
	{
		if (value == '1')
			return ("textures/parede.xpm");
		else if (value == 'P')
			return ("textures/porta.xpm");
		else if (value == 'C')
			return ("textures/sopa.xpm");
		else if (value == 'E')
			return ("textures/pc.xpm");
		else if (value == '0')
			return ("textures/fundo.xpm");
		return (NULL);
	}
	return ("textures/fundo.xpm");
}

int	render_point(t_data *data)
{
	void	*shadow;
	int		i;
	char	*var[3];

	var[0] = ft_itoa(data->cadete.pass);
	var[1] = ft_itoa(data->coin);
	var[2] = ft_itoa(data->score);
	shadow = mlx_xpm_file_to_image(data->mlx, "textures/sombra.xpm", &i, &i);
	mlx_put_image_to_window(data->mlx, data->win,
		shadow, SIZE_Q * data->win_width, 0);
	mlx_destroy_image(data->mlx, shadow);
	mlx_string_put(data->mlx, data->win,
		SIZE_Q * data->win_width, SIZE_Q / 2, 0xFF0000, var[0]);
	mlx_string_put(data->mlx, data->win,
		(SIZE_Q / 2), SIZE_Q / 2, 0xFFFFFF, "  / Sopas :");
	mlx_string_put(data->mlx, data->win, SIZE_Q / 2,
		SIZE_Q / 2, 0xFFFFFF, var[1]);
	shadow = mlx_xpm_file_to_image(data->mlx, "textures/sombra.xpm", &i, &i);
	mlx_put_image_to_window(data->mlx, data->win, shadow, (SIZE_Q / 2) * 6, 0);
	mlx_destroy_image(data->mlx, shadow);
	mlx_string_put(data->mlx, data->win,
		(SIZE_Q / 2) * 6, SIZE_Q / 2, 0xFFD603, var[2]);
	return (free(var[0]), free(var[1]), free(var[2]), 1);
}

void	render_objs(int *i, int *j, int *k, t_data *data)
{
	char	*image_path;
	int		width;
	int		height;

	if (*j > data->win_width * SIZE_Q)
	{
		*k += SIZE_Q;
		*j = SIZE_Q;
	}
	if (data->map[*i].value != 0)
	{
		data->map[*i].pos_x = *j;
		data->map[*i].pos_y = *k;
		image_path = push_image(data->map[*i].value, data);
		if (image_path != NULL)
		{
			data->map[*i].img = mlx_xpm_file_to_image(data->mlx,
					image_path, &width, &height);
			mlx_put_image_to_window(data->mlx, data->win, data->map[*i].img,
				data->map[*i].pos_x, data->map[*i].pos_y);
		}
	}
	*j += SIZE_Q;
}

void	render_map(t_data *data, int time)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = SIZE_Q;
	k = SIZE_Q;
	while (++i < data->win_width * data->win_height)
	{
		render_objs(&i, &j, &k, data);
		if (time == 1)
			usleep(6000);
	}
	ft_free(data);
	ft_print_map(data);
	ft_strcolor("\n", "\033[1;33m");
	render_point(data);
	if (time != 3)
		data->cadete.img_old = animation(data);
	data->cadete.img = mlx_xpm_file_to_image(data->mlx,
			data->cadete.img_old, &i, &j);
	mlx_put_image_to_window(data->mlx, data->win, data->cadete.img,
		data->cadete.pos_x, data->cadete.pos_y);
	mlx_destroy_image(data->mlx, data->cadete.img);
}
