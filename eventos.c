/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eventos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:55:41 by waalexan          #+#    #+#             */
/*   Updated: 2024/06/26 17:57:36 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	on_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

int	move_cadete(int *i, int *current_x, int *current_y, t_data *data)
{
	if (data->img_x == data->map[*i].pos_x
		&& data->img_y == data->map[*i].pos_y)
	{
		if (data->map[*i].value == '1')
		{
			data->img_x = *current_x;
			data->img_y = *current_y;
		}
		else if (data->map[*i].value == 'C')
		{
			data->map[*i].value = 5;
			data->score++;
		}
		else if (data->map[*i].value == 'E')
		{
			if (data->score == data->coin)
			{
				printf("[WIN] Fim do jogo\n");
				free(data->mlx);
				exit(1);
			}
		}
	}
	return (0);
}

int	on_keypress(int keysym, t_data *data)
{
	int	current_x;
	int	current_y;
	int	width;
	int	height;
	int	i;

	i = 0;
	current_x = data->img_x;
	current_y = data->img_y;
	if (keysym == 119)
		data->img_y -= SIZE_Q;
	else if (keysym == 115)
		data->img_y += SIZE_Q;
	else if (keysym == 97)
		data->img_x -= SIZE_Q;
	else if (keysym == 100)
		data->img_x += SIZE_Q;
	while (i < data->win_width * data->win_heigth)
	{
		move_cadete(&i, &current_x, &current_y, data);
		i++;
	}
	mlx_clear_window(data->mlx, data->win);
	render_map(data);
	return (0);
}
