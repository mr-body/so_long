/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eventos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:55:41 by waalexan          #+#    #+#             */
/*   Updated: 2024/06/27 14:17:04 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	on_destroy(t_data *data)
{
	ft_printf("[DADOS] Fim do jogo\nPassos: %d\nscore: %d/%d\n",
		data->passo, data->score, data->coin);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

void	add_food(t_data *data)
{
	data->score++;
	ft_printf("[%d/%d] Sopa Consumida\n", data->score, data->coin);
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
			data->passo--;
			ft_printf("[OBST]");
			return (1);
		}
		else if (data->map[*i].value == 'C')
		{
			data->map[*i].value = 'L';
			add_food(data);
		}
		else if (data->map[*i].value == 'E')
		{
			if (data->score == data->coin)
				on_destroy(data);
		}
	}
	return (0);
}

int	on_keypress(int keysym, t_data *data)
{
	int	current_x;
	int	current_y;
	int	i;

	i = 0;
	current_x = data->img_x;
	current_y = data->img_y;
	data->passo++;
	if (keysym == 119)
		data->img_y -= SIZE_Q;
	else if (keysym == 115)
		data->img_y += SIZE_Q;
	else if (keysym == 97)
		data->img_x -= SIZE_Q;
	else if (keysym == 100)
		data->img_x += SIZE_Q;
	while (i++ < data->win_width * data->win_heigth)
		move_cadete(&i, &current_x, &current_y, data);
	data->img = mlx_xpm_file_to_image(data->mlx, "assets/sombra.xpm",
			&i, &i);
	mlx_put_image_to_window(data->mlx, data->win, data->img,
		current_x, current_y);
	render_map(data);
	ft_printf("[PASSO] %dº passo\n", data->passo);
	return (0);
}
