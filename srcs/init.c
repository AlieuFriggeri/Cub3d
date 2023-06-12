/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:07:45 by vgroux            #+#    #+#             */
/*   Updated: 2023/06/12 18:59:27 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_cub *data, char *av)
{
	if (ft_strncmp(av + (ft_strlen(av) - 4), ".cub", 5) != 0)
		printerror(data, "Not good extension file");
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3d");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->sl, &data->ed);
	init_null(data);
	data->map = openmap(av, data);
	setmapnum(data);
	setmap(data);
	check_color(data);
	if (!check_col(data) || !check_line(data) || !extra_map_check(data))
		printerror(data, "test");
	startpos(data);
	data->player.pdx = cos(data->player.pa) * 5;
	data->player.pdy = sin(data->player.pa) * 5;
}

void	init_null(t_cub *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->wall[i].img = NULL;
		i++;
	}
	data->floor = -1;
	data->sky = -1;
}

void	check_color(t_cub *data)
{
	if (data->sky == -1)
		printerror(data, "Sky color not found");
	else if (data->floor == -1)
		printerror(data, "Floor color not found");
	else if (data->wall[NORTH].img == NULL)
		printerror(data, "North texture not found");
	else if (data->wall[SOUTH].img == NULL)
		printerror(data, "South texture not found");
	else if (data->wall[EAST].img == NULL)
		printerror(data, "East texture not found");
	else if (data->wall[WEST].img == NULL)
		printerror(data, "West texture not found");
}

int	countmap_scandale(int fd, char *res, int x)
{
	int	i;

	i = x;
	free(res);
	res = get_next_line(fd);
	while (res)
	{
		free(res);
		res = get_next_line(fd);
		i++;
	}
	close(fd);
	return (i);
}

void	setmap_scandale2(t_cub *data, int i, int j)
{
	while (j < data->mapx)
	{
		data->mapnum[i][j] = 3;
		j++;
	}
}
