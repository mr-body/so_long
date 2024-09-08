/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:13:56 by waalexan          #+#    #+#             */
/*   Updated: 2024/08/06 18:32:46 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	validate_side(t_data *data)
{
	int	i;
	int	row;

	i = -1;
	while (++i < data->win_width)
		if (data->map[i].value != '1')
			return (0);
	row = (data->win_height * data->win_width - 1);
	i = row - data->win_width;
	while (++i < row)
		if (data->map[i].value != '1')
			return (0);
	i = 0;
	while (++i < data->win_height)
	{
		row = i * data->win_width;
		if (data->map[row].value != '1'
			|| data->map[row + data->win_width - 1].value != '1')
			return (0);
	}
	return (1);
}

int	validate_objects_esp(t_data *data)
{
	int	i;
	int	p;
	int	e;
	int	c;

	p = 0;
	e = 0;
	i = 0;
	c = 0;
	while (i < data->win_width * data->win_height)
	{
		if (data->map[i].value == 'P')
			p++;
		else if (data->map[i].value == 'E')
			e++;
		else if (data->map[i].value == 'C')
			c++;
		else if (data->map[i].value == ' ')
			return (0);
		i++;
	}
	if ((p > 1 || p < 1) || (e > 1 || e < 1) || (c < 1))
		return (0);
	return (1);
}

int	valdate_ext(char *ext)
{
	if (ft_strncmp(ext, ".ber", 4))
		return (0);
	return (1);
}

int	validate_map(char *file, t_data *data)
{
	char	**map;
	int		i;

	if (!valdate_ext(&file[ft_strlen(file) - 4]))
		return (ft_printf("Error\nextensão incorrecta (.ber)\n"), 0);
	if (!validate_side(data))
		return (ft_printf("Error\nParede aberta/caracteres errados\n"), 0);
	if (!validate_objects_esp(data))
		return (ft_printf("Error\nObjectos Faltando 1-P,1-E e C>=1\n"), 0);
	map = matriz(data);
	i = true_way(map, 'C', data);
	if (!i)
		ft_free_valid(data, map);
	i = true_way(map, 'E', data);
	if (!i)
		ft_free_valid(data, map);
	free_matriz(map, data->win_height);
	return (1);
}
