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

void	alloc_map(int *i, char bit, int *j
	, int *k, int *coin, t_map *map, t_data *data)
{
	if (bit == '\n')
	{
		*k += SIZE_Q;
		*j = 0;
	}
	else
	{
		if (bit == '1' || bit == 'P' || bit == 'C' || bit == 'E' || bit == '0')
		{
			map[*i].pos_x = *j;
			map[*i].pos_y = *k;
			map[*i].value = bit;
			if (bit == 'P')
			{
				data->img_x = *j;
				data->img_y = *k;
			}
			else if (bit == 'C')
				(*coin)++;
			(*i)++;
		}
		*j += SIZE_Q;
	}
}

t_map	*create_map(int fd, t_data *data)
{
	char	bit;
	int		i;
	int		j;
	int		k;
	int		coin;
	t_map		*map;

	i = 0;
	j = 0;
	k = 0;
	coin = 0;
	map = malloc((data->win_width * data->win_heigth) * sizeof(t_map));
	while (read(fd, &bit, 1) != 0)
	{
		alloc_map(&i, bit, &j, &k, &coin, map, data);
	}
	data->coin = coin;
	close(fd);
	return (map);
}
