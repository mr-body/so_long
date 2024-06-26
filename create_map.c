/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:27:26 by waalexan          #+#    #+#             */
/*   Updated: 2024/06/26 17:51:47 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display(int fd, t_data *data)
{
	char	bit;
	int		width;
	int		heigth;
	int		fline;

	width = 0;
	heigth = 0;
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
			heigth++;
			fline = 1;
		}
	}
	data->win_width = width;
	data->win_heigth = heigth;
	close(fd);
}

void	alloc_map(int *var, char bit, t_map *map, t_data *data)
{
	if (bit == '\n')
	{
		var[2] += SIZE_Q;
		var[1] = 0;
	}
	else
	{
		if (bit == '1' || bit == 'P' || bit == 'C' || bit == 'E' || bit == '0')
		{
			map[var[0]].pos_x = var[1];
			map[var[0]].pos_y = var[2];
			map[var[0]].value = bit;
			if (bit == 'P')
			{
				data->img_x = var[1];
				data->img_y = var[2];
			}
			else if (bit == 'C')
				(var[3])++;
			(var[0])++;
		}
		var[1] += SIZE_Q;
	}
}

t_map	*create_map(int fd, t_data *data)
{
	char	bit;
	int		var[4];
	t_map	*map;

	var[0] = 0;
	var[1] = 0;
	var[2] = 0;
	var[3] = 0;
	map = malloc((data->win_width * data->win_heigth) * sizeof(t_map));
	while (read(fd, &bit, 1) != 0)
	{
		alloc_map(var, bit, map, data);
	}
	data->coin = var[3];
	close(fd);
	return (map);
}
