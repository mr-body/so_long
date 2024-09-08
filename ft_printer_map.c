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

void	ft_print_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	ft_clear();
	ft_printf("\n%c%c", 32, 32);
	while (i < data->win_width * data->win_height)
	{
		if (j > data->win_width)
		{
			ft_printf("\n%c%c", 32, 32);
			j = 1;
		}
		if (data->map[i].value != 0)
		{
			ft_verific(data->map[i].value);
		}
		j++;
		i++;
	}
}

void	ft_verif_arg(int ac, t_data *data)
{
	if (ac != 2)
	{
		ft_putstr("Error\n./so_long [Path]\n");
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(1);
	}
}

void	ft_free_path_error(t_data *data)
{
	ft_printf("Error\nArquivo invalido\n");
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(1);
}
