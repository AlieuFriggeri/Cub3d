/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:52:12 by vgroux            #+#    #+#             */
/*   Updated: 2023/06/09 13:17:48 by vgroux           ###   ########.fr       */
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
		printerror(data, "malloc error");
	data->wall[wall].img = mlx_xpm_file_to_image(data->mlx, tmp[0],
			&data->wall[wall].width, &data->wall[wall].height);
	ft_free_arr(tmp);
	if (data->wall[wall].img == NULL)
		printerror(data, "Texture not good (maybe the file doesn't exist or it isn't a .xpm file)");
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

void	print_texture(t_cub *data, double rx, int x, int y, int wall)
{
	float	imgx;
	float	offset;
	int		color;

	imgx = (float)((int)rx % CUBSIZE);
	imgx = imgx / (float)CUBSIZE * (float)data->wall[wall].width;
	offset = (float)data->wall[wall].height / (float)data->player.lineH;
	offset *= (float)y;
	color = get_color_from_texture(data, (int)imgx, (int)offset, wall);
	my_mlx_pixel_put(data, x, y + data->player.lineO, color);
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

void	texture(t_cub *data, char *av)
{
	char	**arg;

	if (av && av[0] != '\n')
	{
		printf("%s\n", av);
		arg = ft_split(av, ' ');
		if (!arg)
			printerror(data, "malloc error");
		if (ft_strncmp(arg[0], "NO", 2) == 0)
			get_texture(data, arg[1], NORTH);
		else if (ft_strncmp(arg[0], "SO", 2) == 0)
			get_texture(data, arg[1], SOUTH);
		else if (ft_strncmp(arg[0], "WE", 2) == 0)
			get_texture(data, arg[1], WEST);
		else if (ft_strncmp(arg[0], "EA", 2) == 0)
			get_texture(data, arg[1], EAST);
		else if (ft_strncmp(arg[0], "F", 1))
			get_color(data, &data->floor, arg[1]);
		else if (ft_strncmp(arg[0], "C", 1))
			get_color(data, &data->sky, arg[1]);
		else
			printerror(data, "Config issue");
		ft_free_arr(arg);
		free(av);
	}
	else if (av[0] == '\n')
		free(av);
}

void	get_color(t_cub *data, int *p, char *str)
{
	char	**arg;
	int		r;
	int		g;
	int		b;

	arg = ft_split(str, ',');
	if (!arg)
		printerror(data, "malloc error");
	r = ft_atoi(arg[0]);
	g = ft_atoi(arg[1]);
	b = ft_atoi(arg[2]);
	if (r > 255 || g > 255 || b > 255)
		printerror(data, "config error: color can't me higher than 255");
	else if (r < 0 || g < 0 || b < 0)
		printerror(data, "config error: color can't be negative");
	*p = encode_rgb(r, g, b);
	ft_free_arr(arg);
}
