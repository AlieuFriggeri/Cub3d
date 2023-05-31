/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:08:49 by afrigger          #+#    #+#             */
/*   Updated: 2023/06/07 13:04:55 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

// char	*map[] = {
// 	"11111111",
// 	"10100001",
// 	"100W0001",
// 	"10000101",
// 	"10001001",
// 	"10000101",
// 	"10100101",
// 	"11111111",
// 	NULL
// };

int	main(int ac, char **av)
{
	t_cub	data;
	(void)ac;
	(void)av;
	/*
	if (check_arg(argc, argv, env) == 0)
		init(&data, argc, argv, env);
	*/
	data.player.px = -1;
	data.player.py = -1;
	data.map = openmap(av[1]);
	init(&data, 0, NULL, NULL);
	get_texture(&data, "xpm/test.xpm", 0);
	draw_image(&data);
	add_hook(&data);
	return (0);
}

void	drawmap(t_cub *data)
{
	int i;
	int j;
	int x;
	int y;

	i = 0;
	y = 0;
	while (i < data->mapsize)
	{
		x = 0;
		j = 0;
		while (j < data->mapx)
		{ 	if (j == data->mapx - 1)
			{
				i++;
				break;
			}
			if (data->intmap[i] == 1)
				drawsquare(x, y, data, 1);
			else if (data->intmap[i] == 0)
				drawsquare(x, y, data, 0);
			else 
				drawsquare(x, y, data, 2);
			j++;
			i++;
			x += 8;
		}
		y += 8;
	}
	printf("%d | %d\n", i, data->mapsize);
}

void startpos(t_cub *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S' || data->map[i][j] == 'W' || data->map[i][j] == 'E')
			{
				startangle(data, data->map[i][j]);
				data->player.px = CUBSIZE * j + CUBSIZE / 2;
				data->player.py = CUBSIZE * i + CUBSIZE / 2;
			}
			j++;
		}
		j = 0;
		i++;
	}
	if (data->player.px < 0 || data->player.py < 0)
	{
		perror("No player found in map\n");
		exit(1);
	}
}

void	startangle(t_cub *data, char angle)
{
	if (angle == 'N')
		data->player.pa = PI * 1.5;
	else if (angle == 'W')
		data->player.pa = PI;
	else if (angle == 'E')
		data->player.pa = 2 * PI;
	else if (angle == 'S')
		data->player.pa = 0.5 * PI;
	
}

void	fill_all(t_cub *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < WIDTH)
	{
		while (y < HEIGHT)
		{
			my_mlx_pixel_put(data, x, y, 0x000000);
			y++;
		}
		y = 0;
		x++;
	}
}
