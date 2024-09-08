/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:57:17 by waalexan          #+#    #+#             */
/*   Updated: 2024/07/21 17:57:23 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	on_destroy(t_data *data)
{
	ft_printf("[DADOS] Fim do jogo\nPassos: %d\nscore: %d/%d\n",
		data->cadete.pass, data->score, data->coin);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->map);
	free(data->mlx);
	exit(0);
	return (0);
}

void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->win_width * data->win_height)
	{
		mlx_destroy_image(data->mlx, data->map[i].img);
		i++;
	}
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
	exit(1);
}

int	main(int ac, char **av)
{
	t_data	data;

	data.mlx = mlx_init();
	ft_verif_arg(ac, &data);
	if (open(av[1], O_RDONLY) > 0 && valdate_ext(&av[1][ft_strlen(av[1]) - 4]))
	{
		display(open(av[1], O_RDONLY), &data);
		data.map = create_map(open(av[1], O_RDONLY), &data);
		validate_lines(open(av[1], O_RDONLY), &data);
		if (validate_map(av[1], &data))
		{
			data.win = mlx_new_window(data.mlx, (data.win_width + 2) * SIZE_Q,
					(data.win_height + 2) * SIZE_Q, "So_long");
			render_map(&data, 1);
			mlx_hook(data.win, 2, 1L << 0, &on_keypress, &data);
			mlx_hook(data.win, 17, 1L << 0, &on_destroy, &data);
			mlx_loop(data.mlx);
		}
		else
			ft_free_width_error(&data);
	}
	else
		ft_free_path_error(&data);
	return (0);
}
