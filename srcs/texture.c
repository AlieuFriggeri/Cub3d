/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:52:12 by vgroux            #+#    #+#             */
/*   Updated: 2023/07/05 12:15:13 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Return 1 on error
*/
int	get_texture(t_cub *data, char *path, int wall)
{
	char	**tmp;

	tmp = ft_split(path, '\n');
	if (!tmp)
		printerror(data, "Malloc error");
	data->wall[wall].img = mlx_xpm_file_to_image(data->mlx, tmp[0],
			&data->wall[wall].width, &data->wall[wall].height);
	ft_free_arr(tmp);
	if (data->wall[wall].img == NULL)
		printerror(data, "Texture not good");
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

void	print_texture(t_cub *data, double rx, int y, int wall)
{
	float	imgx;
	float	offset;
	int		color;

	imgx = (float)((int)rx % CUBSIZE);
	imgx = imgx / (float)CUBSIZE * (float)data->wall[wall].width;
	offset = (float)data->wall[wall].height / (float)data->player.lineh;
	offset *= (float)y;
	color = get_color_from_texture(data, (int)imgx, (int)offset, wall);
	my_mlx_pixel_put(data, data->ax, y + data->player.lineo, color);
}

int	encode_rgb(int r, int g, int b)
{
	int	color;

	color = 0;
	color += r << 16;
	color += g << 8;
	color += b;
	return (color);
}
