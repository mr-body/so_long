/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eventos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:55:41 by waalexan          #+#    #+#             */
/*   Updated: 2024/07/06 18:30:03 by waalexan         ###   ########.fr       */
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
			data->map[*i].value = '0';
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

int	press_w_a_s_d(int keysym, t_data *data)
{
	if (keysym == 119 || keysym == 65362)
		data->img_y -= SIZE_Q;
	else if (keysym == 115 || keysym == 65364)
		data->img_y += SIZE_Q;
	else if (keysym == 97 || keysym == 65361)
		data->img_x -= SIZE_Q;
	else if (keysym == 100 || keysym == 65363)
		data->img_x += SIZE_Q;
	else if (keysym == 65307 || keysym == 113)
		on_destroy(data);
	else
		return (0);
	return (1);
}

int	on_keypress(int keysym, t_data *data)
{
	int	tmp_x;
	int	tmp_y;
	int	i;

	i = 0;
	tmp_x = data->img_x;
	tmp_y = data->img_y;
	data->passo++;
	if (!press_w_a_s_d(keysym, data))
		return (0);
	while (i++ < data->win_width * data->win_heigth)
		move_cadete(&i, &tmp_x, &tmp_y, data);
	render_map(data, 0);
	ft_printf("[PASSO] %dº passo\n", data->passo);
	return (0);
}
