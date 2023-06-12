/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kistod <kistod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:08:49 by afrigger          #+#    #+#             */
/*   Updated: 2023/06/12 12:43:11 by kistod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	main(int ac, char **av)
{
	t_cub	data;

	(void)ac;
	data.player.px = -1;
	data.player.py = -1;
	data.player.wall_dist = 100000;
	data.mapstart = 0;
	data.map = openmap(av[1], &data);
	int i = 0;
	while (data.map[i])
	{
		printf("%s\n", data.map[i]);
		i++;
	}
	if (check_col(&data) == 0 || check_line(&data) == 0)
		printf("NON\n");
/* 	if (check_map(&data) != 0)
		printf("d'autre soucis\n"); */
/* 	init(&data, 0, NULL, NULL);
	get_texture(&data, "xpm/test.xpm", 0);
	get_texture(&data, "xpm/door.xpm", 1);
	get_texture(&data, "xpm/stone.xpm", 2);
	get_texture(&data, "xpm/corona.xpm", 3);
	draw_image(&data);
	add_hook(&data); */
	return (0);
}

void	startpos(t_cub *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
				startangle(data, data->map[i][j], i, j);
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

void	startangle(t_cub *data, char angle, int i, int j)
{
	if (angle == 'N')
		data->player.pa = PI * 1.5;
	else if (angle == 'W')
		data->player.pa = PI;
	else if (angle == 'E')
		data->player.pa = 2 * PI;
	else if (angle == 'S')
		data->player.pa = 0.5 * PI;
	data->player.px = CUBSIZE * j + CUBSIZE / 2;
	data->player.py = CUBSIZE * i + CUBSIZE / 2;
}
