/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:03:41 by vgroux            #+#    #+#             */
/*   Updated: 2023/06/07 18:14:25 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setplayer(t_cub *data)
{
	int	r;

	r = 0;
	check_angle(data);
	data->player.pa2 = data->player.pa - (DEG / 4) * (NBRAY / 2);
	while (r < NBRAY)
	{
		if (data->player.pa2 < 0)
			data->player.pa2 += 2 * PI;
		else if (data->player.pa2 > 2 * PI)
			data->player.pa2 -= 2 * PI;
		data->player.r = r;
		if (check_horizontal_lines(data, 0) < check_vertical_lines(data, 0))
		{
			data->player.disT = check_horizontal_lines(data, 0);
			check_horizontal_lines(data, 1);
		}
		else
		{
			data->player.disT = check_vertical_lines(data, 0);
			check_vertical_lines(data, 1);
		}
		data->player.pa2 += DEG / 4;
		r++;
	}
}

void	draw_line3d(t_cub *data, float rx, float ry, int vert)
{
	int	y;
	int	x;
	int	x2;

	x = data->player.r * (NBRAY / (NBRAY / 2));
	x2 = x + (NBRAY / (NBRAY / 2));
	while (x < x2)
	{
		y = 0;
		while (y < data->player.lineH)
		{
			select_texture(data, rx, ry, x, y, vert);
			y++;
		}
		x++;
	}
}

void	select_texture(t_cub *data, float rx, float ry, int x, int y, int vert)
{
	if (vert == 1)
	{
		if (data->player.px < rx) // WEST
			print_texture(data, ry, x, y, 3);
		else // EAST
			print_texture(data, ry, x, y, 2);
	}
	else
	{
		if (data->player.py < ry) // SOUTH
			print_texture(data, rx, x, y, 1);
		else // NORTH
			print_texture(data, rx, x, y, 0);
	}
}

float	dist_wallhit(t_cub *data, float rx, float ry)
{
	float	len;
	double	startx;
	double	starty;

	startx = data->player.px;
	starty = data->player.py;
	len = sqrt(pow(rx - startx, 2) + pow(ry - starty, 2));
	return (len);
}
