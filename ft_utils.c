/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:13:06 by waalexan          #+#    #+#             */
/*   Updated: 2024/07/21 18:13:07 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*animation(t_data *data)
{
	if (data->cadete.direction == 'D'
		&& !ft_strncmp(data->cadete.img_old, "textures/D/player1.xpm", 20))
	{
		data->cadete.img_old = "textures/D/player2.xpm";
		return ("textures/D/player2.xpm");
	}
	if (data->cadete.direction == 'F'
		&& !ft_strncmp(data->cadete.img_old, "textures/F/player1.xpm", 20))
	{
		data->cadete.img_old = "textures/F/player2.xpm";
		return ("textures/F/player2.xpm");
	}
	if (data->cadete.direction == 'T'
		&& !ft_strncmp(data->cadete.img_old, "textures/T/player1.xpm", 20))
	{
		data->cadete.img_old = "textures/T/player2.xpm";
		return ("textures/T/player2.xpm");
	}
	if (data->cadete.direction == 'E'
		&& !ft_strncmp(data->cadete.img_old, "textures/E/player1.xpm", 20))
	{
		data->cadete.img_old = "textures/E/player2.xpm";
		return ("textures/E/player2.xpm");
	}
	return (data->cadete.img);
}

void	ft_pos_sprites(int type, int x, int y, t_data *data)
{
	if (type)
	{
		data->cadete.pos_x = x;
		data->cadete.pos_y = y;
	}
	else
	{
		data->soldier.pos_x = x;
		data->soldier.pos_y = y;
	}
}

void	ft_verific(char value)
{
	if (value == '1')
		ft_strcolor("1", "\033[1;36m");
	else if (value == 'P')
		ft_strcolor("P​", "\033[1;34m");
	else if (value == 'C')
		ft_strcolor("C", "\033[1;33m");
	else if (value == 'E')
		ft_strcolor("E​", "\033[1;31m");
	else if (value == '0')
		ft_strcolor("0", "\033[0;30m");
}

void	set_derection(int keysym, t_data *data)
{
	if (keysym == 119 || keysym == 65362)
	{
		data->cadete.direction = 'T';
		data->cadete.img = "textures/T/player1.xpm";
	}
	else if (keysym == 115 || keysym == 65364)
	{
		data->cadete.direction = 'F';
		data->cadete.img = "textures/F/player1.xpm";
	}
	else if (keysym == 97 || keysym == 65361)
	{
		data->cadete.direction = 'E';
		data->cadete.img = "textures/E/player1.xpm";
	}
	else if (keysym == 100 || keysym == 65363)
	{
		data->cadete.direction = 'D';
		data->cadete.img = "textures/D/player1.xpm";
	}
}

int	validate_lines(int fd, t_data *data)
{
	char	bit;
	int		width;

	width = 0;
	while (read(fd, &bit, 1) != 0)
	{
		if (bit == '\n')
		{
			if (width != data->win_width)
			{
				ft_printf("Error\nMap descoordenado: ");
				ft_printf("%d -> %d\n", width, data->win_width);
				mlx_destroy_display(data->mlx);
				free(data->map);
				free(data->mlx);
				exit(1);
			}
			width = 0;
		}
		else
			width++;
	}
	return (close(fd), 0);
}
