/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:23:28 by afrigger          #+#    #+#             */
/*   Updated: 2023/05/15 15:48:09 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_exit(t_cub *data)
{
	if (data->window && data->window)
		mlx_destroy_window(data->mlx, data->window);
	if (data->mlx && data->img)
		mlx_destroy_image(data->mlx, data->img);
	exit (0);
}

void	move_player(int keycode, t_cub *data)
{
	if (keycode == 13)
		data->player.py -= 8;
	if (keycode == 0)
		data->player.px -= 8;
	if (keycode == 1)
		data->player.py += 8;
	if (keycode == 2)
		data->player.px += 8;
	if (data->player.px > WIDTH / 2 - 1)
		data->player.px = WIDTH / 2 - 1;
	else if (data->player.px < 0)
		data->player.px = 0;
	if (data->player.py > HEIGHT - 1)
		data->player.py = HEIGHT - 1;
	else if (data->player.py < 0)
		data->player.py = 0;
	fill_all(data);
	draw_image(data);
}

void	rotate_player(int keycode, t_cub *data)
{
	if (keycode == 123)
	{
		data->player.pa -= 0.1;
		if (data->player.pa < 0)
			data->player.pa += 2 * PI;
		data->player.pdx = cos(data->player.pa) * 5;
		data->player.pdy = sin(data->player.pa) * 5;
	}
	if (keycode == 124)
	{
		data->player.pa += 0.1;
		if (data->player.pa > 2 * PI)
			data->player.pa = 0;
		data->player.pdx = cos(data->player.pa) * 5;
		data->player.pdy = sin(data->player.pa) * 5;
	}
	if (keycode == 126)
	{
		data->player.px += data->player.pdx;
		data->player.py += data->player.pdy;
	}
	if (keycode == 125)
	{
		data->player.px -= data->player.pdx;
		data->player.py -= data->player.pdy;
	}
	move_player(keycode, data);
}

int	hook(int keycode, t_cub *data)
{
	if (keycode == 53)
		cub_exit(data);
	else if (keycode == 0 || keycode == 1 || keycode == 2 || keycode == 13)
		move_player(keycode, data);
	else if (keycode == 123 || keycode == 124
		|| keycode == 125 || keycode == 126)
		rotate_player(keycode, data);
	return (0);
}
