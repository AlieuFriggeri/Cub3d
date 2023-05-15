/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:08:49 by afrigger          #+#    #+#             */
/*   Updated: 2023/05/15 15:50:34 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

char	*map[] = {
	"1 1 1 1 1 1 1 1",
	"1 0 1 0 0 0 0 1",
	"1 0 0 0 0 0 0 1",
	"1 0 0 0 0 1 0 1",
	"1 0 0 0 1 0 0 1",
	"1 0 0 0 0 1 0 1",
	"1 0 1 0 0 1 0 1",
	"1 1 1 1 1 1 1 1"
};

int	main(void)
{
	t_cub	data;

	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Cub3d");
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.sizeline, &data.endian);
	data.player.px = 200;
	data.player.py = 256;
	data.mapx = 5;
	data.mapy = 7;
	data.player.pa = PI;
	data.player.pdx = cos(data.player.pa) * 5;
	data.player.pdy = sin(data.player.pa) * 5;
	draw_image(&data);
	mlx_hook(data.window, 02, 0, &hook, &data);
	mlx_hook(data.window, 17, 0, &cub_exit, &data);
	mlx_loop(data.mlx);
	return (0);
}

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
		while (sy < 16)
		{
			if (map[sx][sy] == '1')
				drawsquare(y, x, data, 1);
			else
				drawsquare(y, x, data, 0);
			y += 64;
			sy += 2;
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
	while (map[data->mapx][data->mapy])
		data->mapy++;
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
