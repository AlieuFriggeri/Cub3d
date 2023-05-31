/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:23:28 by afrigger          #+#    #+#             */
/*   Updated: 2023/05/31 12:49:14 by vgroux           ###   ########.fr       */
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

void	check_angle(t_cub *data)
{
	if (data->player.pa == 2 * PI)
		data->player.pa -= 0.001;
	else if (data->player.pa == PI * 1.5)
		data->player.pa -= 0.001;
	else if (data->player.pa == PI / 2)
		data->player.pa += 0.001;
	else if (data->player.pa == PI)
		data->player.pa += 0.001;
}

void	rotate_player(int keycode, t_cub *data)
{
	if (keycode == KEY_LEFT)
	{
		data->player.pa -= 0.1;
		if (data->player.pa <= 0)
			data->player.pa += 2 * PI;
		data->player.pdx = cos(data->player.pa) * 5;
		data->player.pdy = sin(data->player.pa) * 5;
	}
	if (keycode == KEY_RIGHT)
	{
		data->player.pa += 0.1;
		if (data->player.pa >= 2 * PI)
			data->player.pa -= 2 * PI;
		data->player.pdx = cos(data->player.pa) * 5;
		data->player.pdy = sin(data->player.pa) * 5;
	}
	check_angle(data);
}

void	move_player(int keycode, t_cub *data)
{
	if (keycode == KEY_W)
	{
		data->player.px += data->player.pdx;
		data->player.py += data->player.pdy;
	}
	if (keycode == KEY_S)
	{
		data->player.px -= data->player.pdx;
		data->player.py -= data->player.pdy;
	}
	if (keycode == KEY_A)
	{
		data->player.px += data->player.pdy;
		data->player.py -= data->player.pdx;
	}
	if (keycode == KEY_D)
	{
		data->player.px -= data->player.pdy;
		data->player.py += data->player.pdx;
	}
}

int	hook(int keycode, t_cub *data)
{
	if (keycode == KEY_ESC)
		cub_exit(data);
	else
	{
		rotate_player(keycode, data);
		move_player(keycode, data);
		draw_image(data);
	}
	return (0);
}

