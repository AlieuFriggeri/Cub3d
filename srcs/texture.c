/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:52:12 by vgroux            #+#    #+#             */
/*   Updated: 2023/05/31 15:11:49 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Return 1 on error
*/
int	get_texture(t_cub *data, char *path, int wall)
{
	data->wall[wall].img = mlx_xpm_file_to_image(data->mlx, path,
			&data->wall[wall].width, &data->wall[wall].height);
	data->wall[wall].addr = mlx_get_data_addr(data->wall[wall].img,
			&data->wall[wall].bpp, &data->wall[wall].sl, &data->wall[wall].ed);
	return (0);
}

int	get_color_from_texture(t_cub *data, int x, int y, int wall)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	char			*str;
	int				size;

	str = data->wall[wall].addr;
	size = data->wall[wall].width;
	b = str[(x * 4) + (size * y * 4)];
	g = str[(x * 4) + (size * y * 4) + 1];
	r = str[(x * 4) + (size * y * 4) + 2];
	return (((int)r << 16) + ((int)g << 8) + (int)b);
}

void	print_texture(t_cub *data, double ratiox, int x, int y, int wall)
{
	int		imgx;
	imgx = (int)(ratiox * data->wall[wall].width);
	my_mlx_pixel_put(data, x, y + data->player.lineO, get_color_from_texture(data, imgx, y, 0));
}
