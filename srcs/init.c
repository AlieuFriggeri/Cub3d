/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:07:45 by vgroux            #+#    #+#             */
/*   Updated: 2023/05/24 12:11:08 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_cub *data, int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;

	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3d");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->sizeline, &data->endian);
	startpos(data);
	// data->player.px = 200;
	// data->player.py = 220;
	mapsize(data);
	// si au lancement pa == axe retirer 0->01
	//data->player.pa = PI;
	data->player.pdx = cos(data->player.pa) * 5;
	data->player.pdy = sin(data->player.pa) * 5;
}
