/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validar_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:12:42 by waalexan          #+#    #+#             */
/*   Updated: 2024/07/11 14:33:25 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	validar_side(t_data *data)
{
	int	i;
	int	row;

	i = 0;
	while (++i < data->win_width)
	{
		if (data->map[i].value != '1')
			return (0);
	}
	row = (data->win_heigth * data->win_width);
	i = row - data->win_width;
	while (++i < row)
	{
		if (data->map[i].value != '1')
			return (0);
	}
	i = 0;
	while (++i < data->win_heigth)
	{
		row = i * data->win_width;
		if (data->map[row].value != '1'
			|| data->map[row + data->win_width - 1].value != '1')
			return (0);
	}
	return (1);
}

int	validar_obectos(t_data *data)
{
	int		i;
	char	obj;

	i = 0;
	while (i < data->win_width * data->win_heigth)
	{
		obj = data->map[i].value;
		if (!(obj == 'P' || obj == 'E' || obj == 'C'
				|| obj == '0' || obj == '1'))
			return (0);
		i++;
	}
	return (1);
}

int	valdar_ext(char *ext)
{
	if (ft_strncmp(ext, ".ber", 4))
		return (0);
	return (1);
}

int	validar_obectos_esp(t_data *data)
{
	int	i;
	int	p;
	int	e;
	int	c;

	p = 0;
	e = 0;
	i = 0;
	c = 0;
	while (i < data->win_width * data->win_heigth)
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

int	validar_map(char *file, t_data *data)
{
	if (!valdar_ext(&file[ft_strlen(file) - 4]))
	{
		ft_printf("Error\nA extensão do arquivo deve ser .ber\n");
		return (0);
	}
	if (!validar_obectos(data))
	{
		ft_printf("Error\nSó são permitidos os códigos(1,0,E,P,C)\n");
		return (0);
	}
	if (!validar_side(data))
	{
		ft_printf("Error\nAs paredes devem ser todas fechadas\n");
		return (0);
	}
	if (!validar_obectos_esp(data))
	{
		ft_printf("Error\nO jogo deve ser jogavel 1-P,1-E e C>=1\n");
		return (0);
	}
	return (1);
}
