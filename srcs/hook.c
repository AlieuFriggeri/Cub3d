/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:23:28 by afrigger          #+#    #+#             */
/*   Updated: 2023/05/30 16:06:08 by vgroux           ###   ########.fr       */
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
	if (keycode == KEY_W)
		data->player.py -= 8;
	if (keycode == KEY_A)
		data->player.px -= 8;
	if (keycode == KEY_S)
		data->player.py += 8;
	if (keycode == KEY_D)
		data->player.px += 8;
	// if (data->player.px > WIDTH - 1)
	// {
	// 	printf("to much px");
	// 	data->player.px = WIDTH - 1;
	// }
	// else if (data->player.px < 0)
	// {
	// 	printf("to low px");
	// 	data->player.px = 0;
	// }
	// if (data->player.py > HEIGHT - 1)
	// {
	// 	printf("to much py")	;
	// 	data->player.py = HEIGHT - 1;
	// }
	// else if (data->player.py < 0)
	// {
	// 	printf("to low py");
	// 	data->player.py = 0;
	// }
	fill_all(data);
	draw_image(data);
}

void	rotate_player(int keycode, t_cub *data)
{
	if (keycode == KEY_LEFT) // fleche gauche
	{
		data->player.pa -= 0.1;
		if (data->player.pa <= 0)
			data->player.pa += 2 * PI;
		data->player.pdx = cos(data->player.pa) * 5;
		data->player.pdy = sin(data->player.pa) * 5;
	}
	if (keycode == KEY_RIGHT) // fleche droite
	{
		data->player.pa += 0.1;
		if (data->player.pa >= 2 * PI)
			data->player.pa -= 2 * PI;
		data->player.pdx = cos(data->player.pa) * 5;
		data->player.pdy = sin(data->player.pa) * 5;
	}
	if (keycode == KEY_UP) // fleche haut
	{
		data->player.px += data->player.pdx;
		data->player.py += data->player.pdy;
	}
	if (keycode == KEY_DOWN) // fleche bas
	{
		data->player.px -= data->player.pdx;
		data->player.py -= data->player.pdy;
	}
	check_angle(data);
	move_player(keycode, data);
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

int	hook(int keycode, t_cub *data)
{
	if (keycode == KEY_ESC)
		cub_exit(data);
	else if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S || keycode == KEY_D)
		move_player(keycode, data);
	else if (keycode == KEY_UP || keycode == KEY_LEFT
		|| keycode == KEY_DOWN || keycode == KEY_RIGHT)
		rotate_player(keycode, data);
	return (0);
}
