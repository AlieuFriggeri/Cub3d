/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:08:49 by afrigger          #+#    #+#             */
/*   Updated: 2023/05/10 14:17:39 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../headers/hook.h"

char *map[] =
{
	"1 1 1 1 1 1 1 1",
	"1 0 0 0 0 0 0 1",
	"1 0 0 0 0 0 0 1",
	"1 0 0 0 0 0 0 1",
	"1 0 0 0 1 0 0 1",
	"1 0 0 0 0 0 0 1",
	"1 0 0 0 0 0 0 1",
	"1 1 1 1 1 1 1 1"
};

void	my_mlx_pixel_put(t_cub *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->sizeline + x * (data->bitsperpixel / 8));
	*(unsigned int *)dst = color;
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
			sy +=2;
		}
		y = 0;
		sy = 0;
		sx++;
		x += 64;
	}
	//mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
}

int rayCalc(t_cub *data){
	int res;

	data->player.m = tan(data->player.pa / DEG);
	data->player.n = data->player.py - (tan(data->player.pa / DEG) * data->player.px);
	res = data->player.m * data->player.px + data->player.n;
	return res;
}

void rayDraw(t_cub *data){
	int len;

	len = 0;
	data->player.startx = data->player.px;
	data->player.starty = data->player.py;
	while (len < 50)
	{
		my_mlx_pixel_put(data, data->player.startx, data->player.starty, 0x00FF0F);

		len++;
		data->player.startx += cos(data->player.pa);
		data->player.starty+= sin(data->player.pa);
		//my_mlx_pixel_put(data, data->player.pdx + len, data->player.pdy + len, 0xFF0000);
	}
	//my_mlx_pixel_put(data, data->player.pdx, data->player.pdy, 0xFF0000);
}


void	drawsquare(int x, int y, t_cub *data, int type)
{
	int x2;
	int y2;

	x2 = x + 64;
	y2 = y + 64;
	while (x < x2)
	{
		while (y < y2)
		{
			if (y == y2 -1)
				my_mlx_pixel_put(data, x, y, 0x000000);
			else if (type == 1)
				my_mlx_pixel_put(data, x, y, 0x00AA00);
			else
				my_mlx_pixel_put(data, x, y, 0xAA00AA);
			if (x == x2 - 1)
				my_mlx_pixel_put(data, x, y, 0x000000);
			y++;
		}
		y = y2 - 64;
		x++;
	}
}

void	fill_all(t_cub *data)
{
	int x;
	int y;

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

void	setplayer(t_cub *data)
{
	int x;
	int y;
	x = data->player.px;
	y = data->player.py;

	while (x < data->player.px + 10)
	{
		while (y < data->player.py + 10)
		{
			my_mlx_pixel_put(data, x - 5, y - 5, 0xFFF000);
			y++;
		}
		y = data->player.py;
		x++;
	}
	x = 0;
	y = 0;
	// while (x < 100)
	// {
	// 	while (y < 50)
	// 	{
	// 		my_mlx_pixel_put(data, y + data->player.pdx + data->player.px, y + data->player.pdy + data->player.py, 0xFFF000);
	// 		y++;
	// 	}
	// 	y = 0;
	// 	x++;
	// }
	rayDraw(data);
	mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
}

int main()
{
	t_cub	data;

	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Cub3d");
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bitsperpixel, &data.sizeline, &data.endian);
	data.player.px = 512;
	data.player.py = 256;
	data.mapx = 5;
	data.mapy = 7;
	data.player.pa = PI;
	data.player.pdx = cos(data.player.pa) * 5;
	data.player.pdy = sin(data.player.pa) * 5;
	drawmap(&data);
	setplayer(&data);
	mlx_hook(data.window, 02, 0, &hook, &data);
	mlx_hook(data.window, 17, 0, &cub_exit, &data);
	mlx_loop(data.mlx);
	return (0);
;}