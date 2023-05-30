/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:29:24 by vgroux            #+#    #+#             */
/*   Updated: 2023/05/30 15:15:28 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor(t_cub *data)
{
	int	x;
	int	y;

	x = 0;
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			my_mlx_pixel_put(data, x, y, GREY_COLOR);
			x++;
		}
		y++;
		x = 0;
	}
}

void	draw_sky(t_cub *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < HEIGHT / 2)
	{
		while (x < WIDTH)
		{
			my_mlx_pixel_put(data, x, y, BLUE_COLOR);
			x++;
		}
		y++;
		x = 0;
	}
}

void	draw_image(t_cub *data)
{
	draw_sky(data);
	draw_floor(data);
	drawmap(data);
	setplayer(data);
}
