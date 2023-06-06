/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:07:45 by vgroux            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/06/07 13:07:06 by vgroux           ###   ########.fr       */
=======
/*   Updated: 2023/06/06 14:06:12 by vgroux           ###   ########.fr       */
>>>>>>> probleme malloc localiser (texture.c:get_texture:mlx_xpm_file_to_image)
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
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->sl, &data->ed);
	startpos(data);
	setmap(data);
	printf("apres setmap()\n");
	data->player.pdx = cos(data->player.pa) * 5;
	data->player.pdy = sin(data->player.pa) * 5;
}
