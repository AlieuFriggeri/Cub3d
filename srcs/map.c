/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:31:11 by vgroux            #+#    #+#             */
/*   Updated: 2023/06/07 12:05:16 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**openmap(char *path)
{
	int fd;
	int i;
	char **map1;
	int size;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit(1);
	size = countmapsize(fd);
	map1 = malloc(sizeof(char *) * size + 1);
	i = 0;
	fd = open(path, O_RDONLY);
	while (i <= size)
	{
		map1[i] = get_next_line(fd);
		if (map1[i] == NULL)
			break ;
		i++;
	}
	close(fd);
	return map1;
}

void	setmap(t_cub *data)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	alloc_intmap(data);
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '0' || data->map[i][j] == 'S' || data->map[i][j] == 'N' || data->map[i][j] == 'W' || data->map[i][j] == 'S')
				data->intmap[k] = 0;
			else
				data->intmap[k] = 1;
			j++;
			k++;
		}
		i++;
	}
	mapsizeint(data);
}

void	alloc_intmap(t_cub *data)
{
	int size;
	int i;
	
	i = 0;
	size = 0;
	while (data->map[i])
	{
		size += ft_strlen(data->map[i]);
		i++;
	}
	data->intmap = malloc(sizeof(int) * (size - i) + 1);
}

int	countmapsize(int fd)
{
	int i;

	i = 0;
	while (get_next_line(fd))
		i++;
	close(fd);
	return (i);
}

void	mapsizeint(t_cub *data)
{
	int i;
	int max;
	
	i = 0;
	max = 0;
	while (data->map[i])
	{
		if ((int)ft_strlen(data->map[i]) > max)
			max = ft_strlen(data->map[i]);
		i++;
	}
	data->mapx = max;
	data->mapy = i;
	data->mapsize = max * i;
}
