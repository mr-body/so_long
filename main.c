#include "so_long.h"

void	display(int fd, t_data *data)
{
	char	bit;
	int		width = 0;
	int		heigth = 0;
	int		fline = 0;

	while (read(fd, &bit, 1) != 0)
	{
		if(bit != '\n')
		{
			if(fline == 0)
				width++;
		}
		else
		{
			heigth++;
			fline = 1;
		}
	}
	
	data->win_width = width;
	data->win_heigth = heigth;
	close(fd);
}

t_map	*create_map(int fd, t_data *data, int flg)
{
	int size = data->win_width * data->win_heigth;
	int i = 0;
	char bit;
	int j = 0;
	int k = 0;
	int width = 1;
	int height = 1;
	
	t_map *map = malloc(size * sizeof(t_map));
	
	while (read(fd, &bit, 1) != 0)
	{	
		if(bit == '\n')
		{
			k +=SIZE_Q;
			j = 0;
		}
		else
		{
			if(bit == '1')
			{
				map[i].pos_x = j;
				map[i].pos_y = k;
				map[i].value = 1;
				map[i].img = mlx_xpm_file_to_image(data->mlx, "assets/parede.xpm", &width, &height);
				mlx_put_image_to_window(data->mlx, data->win, map[i].img, map[i].pos_x, map[i].pos_y);
				i++;
			}
			else if(bit == 'P')
			{
				map[i].pos_x = j;
				map[i].pos_y = k;
				map[i].value = 2;
				map[i].img = mlx_xpm_file_to_image(data->mlx, "assets/porta.xpm", &width, &height);
				mlx_put_image_to_window(data->mlx, data->win, map[i].img, map[i].pos_x, map[i].pos_y);
				if(flg)
				{
					data->img_x = j;
					data->img_y = k;
				}
				i++;
			}
			else if(bit == 'C')
			{
				map[i].pos_x = j;
				map[i].pos_y = k;
				map[i].value = 3;
				map[i].img = mlx_xpm_file_to_image(data->mlx, "assets/sopa.xpm", &width, &height);
				mlx_put_image_to_window(data->mlx, data->win, map[i].img, map[i].pos_x, map[i].pos_y);
				i++;
			}
			else if(bit == 'E')
			{
				map[i].pos_x = j;
				map[i].pos_y = k;
				map[i].value = 4;
				map[i].img = mlx_xpm_file_to_image(data->mlx, "assets/pc.xpm", &width, &height);
				mlx_put_image_to_window(data->mlx, data->win, map[i].img, map[i].pos_x, map[i].pos_y);
				i++;
			}		
			j+= SIZE_Q;
		}
	}
	
	data->img = mlx_xpm_file_to_image(data->mlx, "assets/cadete.xpm", &width, &height);
	mlx_put_image_to_window(data->mlx, data->win, data->img, data->img_x, data->img_y);
	
	close(fd);
	
	return map;
} 


int on_destroy(t_data *data) {
    mlx_destroy_window(data->mlx, data->win);
    mlx_destroy_display(data->mlx);
    free(data->mlx);
    exit(0);
    return 0;
}

int on_keypress(int keysym, t_data *data)
{
    // Salvar as coordenadas atuais do avatar
    int current_x = data->img_x;
    int current_y = data->img_y;

    // Atualizar as coordenadas do avatar conforme a tecla pressionada
    if (keysym == XK_w) {
        data->img_y -= SIZE_Q; // move up
    } else if (keysym == XK_s) {
        data->img_y += SIZE_Q; // move down
    } else if (keysym == XK_a) {
        data->img_x -= SIZE_Q; // move left
    } else if (keysym == XK_d) {
        data->img_x += SIZE_Q; // move right
    }

    // Verificar se a nova posição do avatar está ocupada por uma parede
    int i = 0;
    while(i < data->win_width * data->win_heigth) {
        if (data->img_x == data->map[i].pos_x && data->img_y == data->map[i].pos_y) {
            if (data->map[i].value == 1) { // Se houver uma parede na nova posição
                // Restaurar as coordenadas originais do avatar
                data->img_x = current_x;
                data->img_y = current_y;
                break; // Sair do loop
            }
        }
        i++;
    }

    // Limpar a janela e renderizar o mapa atualizado
    mlx_clear_window(data->mlx, data->win);
    create_map(open("./map/map.ber", O_RDONLY), data, 0);

    return (0);
}



int	main(int ac, char **av)
{
	int	fd;
	int width, height;
	t_data data;
	
	data.mlx = mlx_init();

	if (ac != 2)
	{
		if (ac > 2)
			write(1, "Too many arguments.\n", 20);
		if (ac < 2)
			write(1, "File name missing.\n", 19);
		return (1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd > 0)
	{
		display(fd, &data);
		data.win = mlx_new_window(data.mlx, data.win_width * SIZE_Q, data.win_heigth * SIZE_Q, "So_long");
		if (!data.win)
        	return (free(data.mlx), 1);
        
        data.map = create_map(open(av[1], O_RDONLY), &data, 1);
        
       	mlx_hook(data.win, KeyPress, KeyPressMask, &on_keypress, &data);
    	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
		mlx_loop(data.mlx);		
	}
	else
	{
		write (1, "Cannot read file.\n", 18);
		return (1);
	}
	close(fd);
	return (0);
}
