/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:03:41 by vgroux            #+#    #+#             */
/*   Updated: 2023/05/10 15:13:08 by vgroux           ###   ########.fr       */
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
	raydraw(data);
	mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
}

void	raydraw(t_cub *data)
{
	int		len;
	double	startx;
	double	starty;

	len = 0;
	startx = data->player.px;
	starty = data->player.py;
	while (len < 50)
	{
		my_mlx_pixel_put(data, startx, starty, 0x00FF0F);
		startx += cos(data->player.pa);
		starty += sin(data->player.pa);
		len++;
	}
}
