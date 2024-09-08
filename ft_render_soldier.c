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

#include "so_long.h"

int	move_soldier(int *i, int *current_x, int *current_y, t_data *data)
{
	if (data->soldier.pos_x == data->map[*i].pos_x
		&& data->soldier.pos_y == data->map[*i].pos_y)
	{
		if (data->cadete.pos_x == data->soldier.pos_x
			&& data->cadete.pos_y == data->soldier.pos_y)
			on_destroy(data);
		if (data->map[*i].value == '1')
		{
			data->soldier.pos_x = *current_x;
			data->soldier.pos_y = *current_y;
			return (1);
		}
		else if (data->map[*i].value == 'C')
		{
			data->soldier.shadow_inter = 1;
			data->soldier.shadow = "textures/sopa.xpm";
		}
		else if (data->map[*i].value == 'E')
		{
			data->soldier.shadow_inter = 1;
			data->soldier.shadow = "textures/pc.xpm";
		}
	}
	return (0);
}

int	ft_command(int keysym, t_data *data)
{
	if (keysym == 119 || keysym == 65362)
		data->soldier.pos_y -= SIZE_Q;
	else if (keysym == 115 || keysym == 65364)
		data->soldier.pos_y += SIZE_Q;
	else if (keysym == 97 || keysym == 65361)
		data->soldier.pos_x -= SIZE_Q;
	else if (keysym == 100 || keysym == 65363)
		data->soldier.pos_x += SIZE_Q;
	else
		return (0);
	return (1);
}

int	ft_render_soldier(int keysym, t_data *data)
{
	int	tmp_x;
	int	tmp_y;
	int	i;

	i = 0;
	tmp_x = data->soldier.pos_x;
	tmp_y = data->soldier.pos_y;
	if (!ft_command(keysym, data))
		return (0);
	while (++i < data->win_width * data->win_height)
	{
		if (move_soldier(&i, &tmp_x, &tmp_y, data))
			return (0);
	}
	render_map(data, 3);
	return (1);
}
