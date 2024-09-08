/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eventos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:03:55 by waalexan          #+#    #+#             */
/*   Updated: 2024/07/21 18:03:57 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_close_game(t_data *data)
{
	data->end = 1;
	render_map(data, 1);
	on_destroy(data);
}

int	move_cadete(int *i, int *current_x, int *current_y, t_data *d)
{
	if (d->cadete.pos_x == d->map[*i].pos_x
		&& d->cadete.pos_y == d->map[*i].pos_y)
	{
		if (d->cadete.pos_x == d->soldier.pos_x
			&& d->cadete.pos_y == d->soldier.pos_y)
			ft_close_game(d);
		if (d->map[*i].value == '1')
		{
			d->cadete.pos_x = *current_x;
			d->cadete.pos_y = *current_y;
			return (d->cadete.pass--, 1);
		}
		else if (d->map[*i].value == 'C')
		{
			d->map[*i].value = '0';
			d->score++;
		}
		else if (d->map[*i].value == 'E')
		{
			if (d->score == d->coin)
				on_destroy(d);
		}
	}
	return (0);
}

int	press_w_a_s_d(int keysym, t_data *data)
{
	if (keysym == 119 || keysym == 65362)
		data->cadete.pos_y -= SIZE_Q;
	else if (keysym == 115 || keysym == 65364)
		data->cadete.pos_y += SIZE_Q;
	else if (keysym == 97 || keysym == 65361)
		data->cadete.pos_x -= SIZE_Q;
	else if (keysym == 100 || keysym == 65363)
		data->cadete.pos_x += SIZE_Q;
	else if (keysym == 65307 || keysym == 113)
	{
		data->cadete.pass--;
		on_destroy(data);
	}
	else
		return (0);
	set_derection(keysym, data);
	return (1);
}

int	on_keypress(int keysym, t_data *data)
{
	int	tmp_x;
	int	tmp_y;
	int	i;
	int	flg;

	i = 0;
	flg = 1;
	tmp_x = data->cadete.pos_x;
	tmp_y = data->cadete.pos_y;
	data->cadete.pass++;
	if (!press_w_a_s_d(keysym, data))
		return (0);
	while (i < data->win_width * data->win_height)
	{
		if (move_cadete(&i, &tmp_x, &tmp_y, data))
			flg = 0;
		i++;
	}
	if (flg)
		render_map(data, 0);
	return (0);
}
