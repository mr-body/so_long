/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:20:51 by waalexan          #+#    #+#             */
/*   Updated: 2024/07/11 14:48:52 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int ac, char **av)
{
	t_data	data;

	data.mlx = mlx_init();
	if (ac != 2)
		write(1, "./game [Path].\n", 16);
	else if (open(av[1], O_RDONLY) > 0)
	{
		display(open(av[1], O_RDONLY), &data);
		data.map = create_map(open(av[1], O_RDONLY), &data);
		if (validar_map(av[1], &data))
		{
			data.win = mlx_new_window(data.mlx, (data.win_width + 2) * SIZE_Q,
					(data.win_heigth + 4) * SIZE_Q, "So_long");
			if (!data.win)
				return (free(data.mlx), 1);
			render_map(&data, 1);
			mlx_hook(data.win, 2, 1L << 0, &on_keypress, &data);
			mlx_hook(data.win, 17, 1L << 0, &on_destroy, &data);
			mlx_loop(data.mlx);
		}
	}
	else
		ft_printf("Error\nTem algum problema com o arquivo\n");
	return (0);
}
