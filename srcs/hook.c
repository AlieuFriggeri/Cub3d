/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:23:28 by afrigger          #+#    #+#             */
/*   Updated: 2023/06/07 13:26:50 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_exit(t_cub *data)
{
	if (data->window && data->window)
		mlx_destroy_window(data->mlx, data->window);
	if (data->mlx && data->img)
		mlx_destroy_image(data->mlx, data->img);
	// if (data->mlx && data->wall[3].img)
	// 	mlx_destroy_image(data->mlx, data->wall[3].img);
	// if (data->mlx && data->wall[2].img)
	// 	mlx_destroy_image(data->mlx, data->wall[2].img);
	// if (data->mlx && data->wall[1].img)
	// 	mlx_destroy_image(data->mlx, data->wall[1].img);
	if (data->mlx && data->wall[0].img)
		mlx_destroy_image(data->mlx, data->wall[0].img);
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

void	check_collision(t_cub *data)
{
	int r = 0;
	int dist;
	data->player.pa2 = data->player.pa - (DEG * 180);
	while (r < 4)
	{
		if (checkHorizontalLines(data, 0) < checkVerticalLines(data, 0))
			dist = checkHorizontalLines(data, 0);
		else
			dist = checkVerticalLines(data, 0);
		if (r == 0)
			data->player.dwall_s = dist;
		if (r == 1)
			data->player.dwall_w = dist;
		if (r == 2)
			data->player.dwall_n = dist;
		if (r == 3)
			data->player.dwall_e = dist;
		data->player.pa2 += DEG * 90;
		r++;
	}
}

void	move_player(int keycode, t_cub *data)
{
	check_collision(data);
	if (keycode == KEY_W && data->player.dwall_n > 15)
	{	
		data->player.px += data->player.pdx;
		data->player.py += data->player.pdy;
	}
	if (keycode == KEY_S && data->player.dwall_s > 15)
	{
		data->player.px -= data->player.pdx;
		data->player.py -= data->player.pdy;
	}
	if (keycode == KEY_A && data->player.dwall_w > 15)
	{
		data->player.px += data->player.pdy;
		data->player.py -= data->player.pdx;
	}
	if (keycode == KEY_D && data->player.dwall_e > 15)
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
