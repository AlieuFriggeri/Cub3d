/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:08:49 by afrigger          #+#    #+#             */
/*   Updated: 2023/07/04 15:37:36 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	main(int ac, char **av)
{
	t_cub	data;

	data.mlx = NULL;
	data.window = NULL;
	if (ac == 2)
	{
		data.player.px = -1;
		data.player.py = -1;
		data.player.wall_dist = 100000;
		data.mapstart = 0;
		init(&data, av[1]);
		draw_image(&data);
		add_hook(&data);
	}
	else
		printerror(&data, "Not the right amount of argument");
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
		printerror(data, "No player found in map");
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

void	printerror(t_cub *data, char *str)
{
	ft_putstr_fd("cub3d: error: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	cub_exit(data);
}

void	openmap_scandale(t_cub *data, char ***map, int size, char *path)
{
	int		i;
	int		fd;
	char	**map1;

	map1 = *map;
	i = 0;
	fd = open(path, O_RDONLY);
	while (i <= size)
	{
		if (data->mapstart > 0)
		{
			texture(data, get_next_line(fd));
			data->mapstart--;
		}
		else
		{
			map1[i] = get_next_line(fd);
			// printf("%s", map1[i]);
			if (map1[i] == NULL)
				break ;
			else if (map1[i][0] == '\n')
				printerror(data, "Line after the map");
			i++;
		}
	}
	close(fd);
}
