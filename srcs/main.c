/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:20:51 by waalexan          #+#    #+#             */
/*   Updated: 2024/06/26 17:59:11 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int ac, char **av)
{
	t_data	data;

	data.mlx = mlx_init();
	if (ac != 2)
	{
		write(1, "./game [Path].\n", 16);
		return (1);
	}
	if (open(av[1], O_RDONLY) > 0)
	{
		display(open(av[1], O_RDONLY), &data);
		data.win = mlx_new_window(data.mlx, data.win_width * SIZE_Q,
				data.win_heigth * SIZE_Q, "So_long");
		if (!data.win)
			return (free(data.mlx), 1);
		data.map = create_map(open(av[1], O_RDONLY), &data);
		render_map(&data);
		mlx_hook(data.win, 2, 1L << 0, &on_keypress, &data);
		mlx_hook(data.win, 17, 1L << 0, &on_destroy, &data);
		mlx_loop(data.mlx);
	}
	return (0);
}
