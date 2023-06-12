/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:25:35 by vgroux            #+#    #+#             */
/*   Updated: 2023/06/12 15:50:07 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_cub *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->sl + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	drawsquare(int x, int y, t_cub *data, int type)
{
	int	x2;
	int	y2;

	x2 = x + 8;
	y2 = y + 8;
	while (x < x2)
	{
		while (y < y2)
		{
			if (y == y2 - 1)
				my_mlx_pixel_put(data, x, y, 0x000000);
			else if (x == x2 - 1)
				my_mlx_pixel_put(data, x, y, 0x000000);
			else if (type == 1)
				my_mlx_pixel_put(data, x, y, 0x339900);
			else if (type == 0)
				my_mlx_pixel_put(data, x, y, 0xFF0000);
			else
				my_mlx_pixel_put(data, x, y, 0xFFFF00);
			y++;
		}
		y = y2 - 8;
		x++;
	}
}

void	drawmap(t_cub *data)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	y = 0;
	while (i < data->mapsize)
	{
		x = 0;
		j = 0;
		while (j < data->mapx)
		{
			if (j == data->mapx - 1)
			{
				i++;
				break ;
			}
			render_square(data, x, y, i);
			j++;
			i++;
			x += 8;
		}
		y += 8;
	}
}

void	render_square(t_cub *data, int x, int y, int i)
{
	if (data->intmap[i] == 1)
		drawsquare(x, y, data, 1);
	else if (data->intmap[i] == 0)
		drawsquare(x, y, data, 0);
	else
		drawsquare(x, y, data, 2);
}

void	draw_line(t_cub *data, double angle)
{
	int		len;
	double	startx;
	double	starty;

	len = 0;
	startx = data->player.px;
	starty = data->player.py;
	while (len < 400)
	{
		if (startx < WIDTH && starty < WIDTH
			&& startx < HEIGHT && starty < HEIGHT)
			my_mlx_pixel_put(data, startx, starty, 0xFFFFFF);
		startx += cos(angle);
		starty += sin(angle);
		len++;
	}
}
