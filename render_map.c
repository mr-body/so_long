/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:56:24 by waalexan          #+#    #+#             */
/*   Updated: 2024/06/26 17:56:25 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*push_image(char value)
{
	if (value == '1')
		return ("assets/parede.xpm");
	else if (value == 'P')
		return ("assets/porta.xpm");
	else if (value == 'C')
		return ("assets/sopa.xpm");
	else if (value == 'E')
		return ("assets/pc.xpm");
	return (NULL);
}

void	render_objs(int *i, int *j, int *k, t_data *data)
{
	char	*image_path;
	int		width;
	int		height;

	if (*j >= data->win_width * SIZE_Q)
	{
		*k += SIZE_Q;
		*j = 0;
	}
	if (data->map[*i].value != 0)
	{
		data->map[*i].pos_x = *j;
		data->map[*i].pos_y = *k;
		image_path = push_image(data->map[*i].value);
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

void	render_map(t_data *data)
{
	int	size;
	int	i;
	int	j;
	int	k;

	size = data->win_width * data->win_heigth;
	i = 0;
	j = 0;
	k = 0;
	while (i < size)
	{
		render_objs(&i, &j, &k, data);
		i++;
	}
	data->img = mlx_xpm_file_to_image(data->mlx, "assets/cadete.xpm", &i, &j);
	mlx_put_image_to_window(data->mlx, data->win, data->img,
		data->img_x, data->img_y);
}
