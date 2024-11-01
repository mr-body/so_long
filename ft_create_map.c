/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:04:14 by waalexan          #+#    #+#             */
/*   Updated: 2024/07/21 18:04:16 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display(int fd, t_data *data)
{
	char	bit;
	int		width;
	int		height;
	int		fline;

	width = 0;
	height = 0;
	fline = 0;
	while (read(fd, &bit, 1) != 0)
	{
		if (bit != '\n')
		{
			if (fline == 0)
				width++;
		}
		else
		{
			height++;
			fline = 1;
		}
	}
	data->win_width = width;
	data->win_height = height;
	close(fd);
}

int	alloc_map(int *var, char bit, t_map *map, t_data *data)
{
	if (bit == '\n')
	{
		var[2] += SIZE_Q;
		var[1] = SIZE_Q;
	}
	else
	{
		if (bit == '1' || bit == 'P' || bit == 'C' || bit == 'E' || bit == '0')
		{
			map[var[0]].pos_x = var[1];
			map[var[0]].pos_y = var[2];
			map[var[0]].value = bit;
			if (bit == 'P')
				ft_pos_sprites(1, var[1], var[2], data);
			if (bit == 'E')
				ft_pos_sprites(0, var[1], var[2], data);
			else if (bit == 'C')
				(var[3])++;
			(var[0])++;
		}
		else
			return (0);
		var[1] += SIZE_Q;
	}
	return (1);
}

void	ft_local_free_error(t_data *data, t_map *map)
{
	ft_printf("Error\ncaracteres errados(1,0,E,P,C)\n");
	mlx_destroy_display(data->mlx);
	free(map);
	free(data->mlx);
	exit(1);
}

t_map	*create_map(int fd, t_data *data)
{
	char	bit;
	int		var[5];
	t_map	*map;

	ft_bzero(&var, 5 * sizeof(int));
	var[1] = SIZE_Q;
	var[2] = SIZE_Q;
	map = malloc((data->win_width * data->win_height) * sizeof(t_map));
	while (read(fd, &bit, 1) != 0)
	{
		if (!alloc_map(var, bit, map, data))
			ft_local_free_error(data, map);
	}
	data->cadete.pass = 0;
	data->score = 0;
	data->coin = var[3];
	data->cadete.direction = 'T';
	data->cadete.img_old = "textures/player.xpm";
	data->cadete.img = "textures/player.xpm";
	data->soldier.shadow_inter = -1;
	data->end = 0;
	return (close(fd), map);
}
