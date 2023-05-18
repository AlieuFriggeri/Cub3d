/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:08:49 by afrigger          #+#    #+#             */
/*   Updated: 2023/05/18 12:32:18 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

// char	*map[] = {
// 	"1 1 1 1 1 1 1 1",
// 	"1 0 1 0 0 0 0 1",
// 	"1 0 0 0 0 0 0 1",
// 	"1 0 0 0 0 1 0 1",
// 	"1 0 0 0 1 0 0 1",
// 	"1 0 0 0 0 1 0 1",
// 	"1 0 1 0 0 1 0 1",
// 	"1 1 1 1 1 1 1 1"
// };

char	*map[] = {
	"11111111",
	"10100011",
	"10000001",
	"10000101",
	"10001001",
	"100N0101",
	"10100101",
	"11111111",
	NULL
};

int	main(void)
{
	t_cub	data;

	/*
	if (check_arg(argc, argv, env) == 0)
		init(&data, argc, argv, env);
	*/
	data.player.px = -1;
	data.player.py = -1;
	init(&data, 0, NULL, NULL);
	draw_image(&data);
	add_hook(&data);
	return (0);
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
	int	x;
	int	y;
	int	sx;
	int	sy;

	sx = 0;
	sy = 0;
	x = 0;
	y = 0;
	while (sx < 8)
	{
		while (sy < data->mapy)
		{
			if (map[sx][sy] == '1')
				drawsquare(y, x, data, 1);
			else
				drawsquare(y, x, data, 0);
			y += 64;
			sy ++;
		}
		y = 0;
		sy = 0;
		sx++;
		x += 64;
	}
}

void	mapsize(t_cub *data)
{
	data->mapx = 0;
	while (map[data->mapx] != NULL)
		data->mapx++;
	data->mapy = 0;
	while (map[0][data->mapy])
		data->mapy++;
}

void startpos(t_cub *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
			{
				startangle(data, map[i][j]);
				data->player.px = 64 * j + 32;
				data->player.py = 64 * i + 32;
			}
			j++;
		}
		j = 0;
		i++;
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
