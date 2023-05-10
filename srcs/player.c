/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:03:41 by vgroux            #+#    #+#             */
/*   Updated: 2023/05/10 15:39:36 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setplayer(t_cub *data)
{
	int	x;
	int	y;

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
	draw_raycasting(data);
	mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
}

void	draw_raycasting(t_cub *data)
{
	int		n_ray;
	int		i;
	double	base_angle;

	n_ray = 30;
	i = 0;
	base_angle = data->player.pa - (n_ray * DEG);
	while (i < n_ray)
	{
		draw_line(data, base_angle);
		base_angle += 2 * DEG;
		i++;
	}
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
		my_mlx_pixel_put(data, startx, starty, 0xFFFFFF);
		startx += cos(angle);
		starty += sin(angle);
		len++;
	}
}
