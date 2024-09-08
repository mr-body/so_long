/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:01:06 by waalexan          #+#    #+#             */
/*   Updated: 2024/07/21 18:01:08 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_update(t_data *data)
{
	static int	i = 115;
	static int	c = 0;

	if (c == 250)
	{
		if (i == 100 && !ft_render_soldier(i, data))
			i = 97;
		else if (i == 97 && !ft_render_soldier(i, data))
			i = 115;
		else if (i == 115 && !ft_render_soldier(i, data))
			i = 119;
		else if (i == 119 && !ft_render_soldier(i, data))
			i = 100;
		c = 0;
	}
	c++;
	usleep(2000);
	return (0);
}

int	on_destroy(t_data *data)
{
	ft_printf("[DADOS] Fim do jogo\nPassos: %d\nscore: %d/%d\n",
		data->cadete.pass, data->score, data->coin);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data->map);
	exit(0);
	return (0);
}

void	ft_free_valid(t_data *data, char **map)
{
	mlx_destroy_display(data->mlx);
	free(data->map);
	free(data->mlx);
	free_matriz(map, data->win_height);
	ft_printf("Error\nO jogo deve ser jogavel\n");
	exit(1);
}

void	ft_free_width_error(t_data *data)
{
	mlx_destroy_display(data->mlx);
	free(data->map);
	free(data->mlx);
}

int	main(int ac, char **av)
{
	t_data	data;

	data.mlx = mlx_init();
	ft_verif_arg(ac, &data);
	if (open(av[1], O_RDONLY) > 0 && valdate_ext(&av[1][ft_strlen(av[1]) - 4]))
	{
		display(open(av[1], O_RDONLY), &data);
		validate_lines(open(av[1], O_RDONLY), &data);
		data.map = create_map(open(av[1], O_RDONLY), &data);
		if (validate_map(av[1], &data))
		{
			data.win = mlx_new_window(data.mlx, (data.win_width + 2) * SIZE_Q,
					(data.win_height + 2) * SIZE_Q, "So_long");
			render_map(&data, 1);
			mlx_hook(data.win, 2, 1L << 0, &on_keypress, &data);
			mlx_hook(data.win, 17, 1L << 0, &on_destroy, &data);
			mlx_loop_hook(data.mlx, ft_update, &data);
			mlx_loop(data.mlx);
		}
		else
			ft_free_width_error(&data);
	}
	else
		ft_free_path_error(&data);
	return (0);
}
