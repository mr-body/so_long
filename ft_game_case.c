/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:13:56 by waalexan          #+#    #+#             */
/*   Updated: 2024/08/06 18:40:02 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**matriz(t_data *data)
{
	char	**map;
	int		row;
	int		col;
	int		i;

	row = -1;
	col = -1;
	i = 0;
	map = (char **)malloc(sizeof(char *) * data->win_height);
	while (++row < data->win_height)
		map[row] = malloc(sizeof(char) * data->win_width);
	row = 0;
	while (row < data->win_height)
	{
		col = -1;
		while (++col < data->win_width)
		{
			map[row][col] = data->map[i].value;
			i++;
		}
		row++;
	}
	return (map);
}

void	free_matriz(char **matriz, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(matriz[i]);
		i++;
	}
	free(matriz);
}

void	flood_fill(char **matriz, int x, int y, int *found)
{
	if (matriz[x][y] == 'P')
	{
		*found = 1;
		return ;
	}
	if (matriz[x][y] == '1' || matriz[x][y] == 'V')
		return ;
	matriz[x][y] = 'V';
	flood_fill(matriz, x + 1, y, found);
	flood_fill(matriz, x - 1, y, found);
	flood_fill(matriz, x, y + 1, found);
	flood_fill(matriz, x, y - 1, found);
}

int	true_way(char **map, char c, t_data *data)
{
	int	flg;
	int	i;
	int	j;

	i = 0;
	j = 0;
	flg = 0;
	while (i < data->win_height)
	{
		j = 0;
		while (j < data->win_width)
		{
			if (map[i][j] == c)
			{
				flood_fill(map, i, j, &flg);
				if (flg == 0)
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
