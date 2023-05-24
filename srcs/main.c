/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:08:49 by afrigger          #+#    #+#             */
/*   Updated: 2023/05/24 16:34:12 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

// char	*map[] = {
// 	"11111111",
// 	"10100001",
// 	"100W0001",
// 	"10000101",
// 	"10001001",
// 	"10000101",
// 	"10100101",
// 	"11111111",
// 	NULL
// };

//char	**map3;

int	main(int ac, char **av)
{
	t_cub	data;
	(void)ac;
	(void)av;
	/*
	if (check_arg(argc, argv, env) == 0)
		init(&data, argc, argv, env);
	*/
	data.player.px = -1;
	data.player.py = -1;
	data.map = openmap(av[1]);
	init(&data, 0, NULL, NULL);
	draw_image(&data);
	add_hook(&data);
	return (0);
}

char	**openmap(char *path)
{
	int fd;
	int i;
	char **map1;
	int size;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit(1);
	size = countmapsize(fd);
	map1 = malloc(sizeof(char *) * size + 1);
	i = 0;
	// while (i < size - 1)
	// {
	// 	map1[i] = malloc(sizeof(char ) * 64);
	// 	i++;
	// }
	// map1[i + 1] = NULL;
	fd = open(path, O_RDONLY);
	while (i <= size)
	{
		map1[i] = get_next_line(fd);
		if (map1[i] == NULL)
			break ;
		i++;
	}
	return map1;
}

int	countmapsize(int fd)
{
	int i;

	i = 0;
	while (get_next_line(fd))
		i++;
	return (i);
}
// int	main(void)
// {
// 	t_cub	data;

// 	data.mlx = mlx_init();
// 	data.window = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Cub3d");
// 	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
// 	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.sizeline, &data.endian);
// 	data.player.px = 200;
// 	data.player.py = 220;
// 	mapsize(&data);
// 	printf("%d | %d \n", data.mapx, data.mapy);
// 	data.mapx = 5;
// 	data.mapy = 7;
// 	// si au lancement pa == axe retirer 0.01
// 	data.player.pa = PI;
// 	data.player.pdx = cos(data.player.pa) * 5;
// 	data.player.pdy = sin(data.player.pa) * 5;
// 	draw_image(&data);
// 	mlx_hook(data.window, 2, 0, &hook, &data);
// 	mlx_hook(data.window, 17, 0, &cub_exit, &data);
// 	mlx_loop(data.mlx);
// 	return (0);
// }

void	drawmap(t_cub *data)
{
	// int	x;
	// int	y;
	// int	sx;
	// int	sy;

	// sx = 0;
	// sy = 0;
	// x = 0;
	// y = 0;
	// mapsizeint(data, sx);
	// printf("\n%d | %d\n", data->mapx, data->mapy);
	// while (sx < data->mapsize)
	// {
	// 	while (sy < data->mapy)
	// 	{
	// 		if (data->map[sx][sy] == '1')
	// 			drawsquare(y, x, data, 1);
	// 		else if (data->map[sx][sy] != '0' && data->map[sx][sy] != '1')
	// 			drawsquare(y, x, data, 2);
	// 		else
	// 			drawsquare(y, x, data, 0);
	// 		y += 16;
	// 		sy++;
	// 	}
	// 	y = 0;
	// 	sy = 0;
	// 	sx++;
	// 	mapsizeint(data, sx);
	// 	x += 16;
	// }

	int i;
	int j;
	int x;
	int y;

	i = 0;
	y = 0;
	mapsizeint(data, 0);
	while (i < data->mapsize)
	{
		x = 0;
		j = 0;
		while (j < data->mapx)
		{
			if (data->intmap[i] == 1)
				drawsquare(x, y, data, 1);
			else if (data->intmap[i] == 0)
				drawsquare(x, y, data, 0);
			else 
				drawsquare(x, y, data, 2);
			j++;
			i++;
			x += 16;
		}
		y += 16;
	}
}

void	mapsize(t_cub *data)
{
	data->mapx = 0;
	while (data->map[data->mapx] != NULL)
		data->mapx++;
	data->mapy = 0;
	while (data->map[0][data->mapy])
		data->mapy++;
}

void	mapsizeint(t_cub *data, int posx)
{
	// int i;

	// i = 0;
	// if (!data->map[posx])
	// 	return;
	// while(data->map[posx][i])
	// 	i++;
	// data->mapy = i - 1;
	int i;
	int max;
	(void)posx;
	i = 0;
	max = 0;
	while (data->map[i])
	{
		if ((int)ft_strlen(data->map[i]) > max)
			max = ft_strlen(data->map[i]);
		i++;
	}
	data->mapx = max;
	data->mapy = i ;
	data->mapsize = max * i;
	//printf("\n%d | %d\n", data->mapx, data->mapy);
}

void startpos(t_cub *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		while (data->map[i][j])
		{
			//printf("i = %d | j = %d\n", i, j);
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S' || data->map[i][j] == 'W' || data->map[i][j] == 'E')
			{
				startangle(data, data->map[i][j]);
				data->player.px = 64 * j + 32;
				data->player.py = 64 * i + 32;
			}
			j++;
		}
		j = 0;
		i++;
				//printf("salut\n");
	}
	if (data->player.px < 0 || data->player.py < 0)
	{
		perror("No player found in map\n");
		exit(1);
	}
}

void	startangle(t_cub *data, char angle)
{
	if (angle == 'N')
		data->player.pa = PI * 1.5;
	else if (angle == 'W')
		data->player.pa = PI;
	else if (angle == 'E')
		data->player.pa = 2 * PI;
	else if (angle == 'S')
		data->player.pa = 0.5 * PI;
	
}

void	fill_all(t_cub *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < WIDTH)
	{
		while (y < HEIGHT)
		{
			my_mlx_pixel_put(data, x, y, 0x000000);
			y++;
		}
		y = 0;
		x++;
	}
}
