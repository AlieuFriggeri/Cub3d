/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:08:49 by afrigger          #+#    #+#             */
/*   Updated: 2023/05/17 16:18:28 by vgroux           ###   ########.fr       */
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

	/*
	if (check_arg(argc, argv, env) == 0)
		init(&data, argc, argv, env);
	*/
	init(&data, 0, NULL, NULL);
	draw_image(&data);
	add_hook(&data);
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
