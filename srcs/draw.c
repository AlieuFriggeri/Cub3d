/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:25:35 by vgroux            #+#    #+#             */
/*   Updated: 2023/05/24 12:29:25 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_cub *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->sizeline + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	drawsquare(int x, int y, t_cub *data, int type)
{
	int	x2;
	int	y2;

	x2 = x + 16;
	y2 = y + 16;
	while (x < x2)
	{
		while (y < y2)
		{
			if (y == y2 -1)
				my_mlx_pixel_put(data, x, y, 0x000000);
			else if (type == 1)
				my_mlx_pixel_put(data, x, y, 0x00AA00);
			else if (type == 2)
				my_mlx_pixel_put(data, x, y, 0xFFF000);
			else
				my_mlx_pixel_put(data, x, y, 0xAA00AA);
			if (x == x2 - 1)
				my_mlx_pixel_put(data, x, y, 0x000000);
			y++;
		}
		y = y2 - 16;
		x++;
	}
}
