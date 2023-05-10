/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:43:18 by vgroux            #+#    #+#             */
/*   Updated: 2023/05/10 16:12:29 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_map(int fd, t_map *map)
{
	char	*buffer;

	buffer = get_next_line(fd);
	while (buffer != NULL)
	{
		if (ft_strncmp(buffer, "NO", 2) == 0)
			map->mesh_north = buffer + 3;
		else if (ft_strncmp(buffer, "SO", 2) == 0)
			map->mesh_south = buffer;
		else if (ft_strncmp(buffer, "WE", 2) == 0)
			map->mesh_west = buffer + 3;
		else if (ft_strncmp(buffer, "EA", 2) == 0)
			map->mesh_east = buffer + 3;
		else if (ft_strncmp(buffer, "F", 1) == 0)
			map->color_floor = get_int_from_rgb(buffer);
		else if (ft_strncmp(buffer, "C", 1))
			map->color_sky = get_int_from_rgb(buffer);
		else if (/* LIGNE VIDE PEUT JUSTE SEPARER PARAM*/)
		{
			
		}
		else
		{
			// C'EST LA MAP
		}
		free(buffer);
		buffer = get_next_line(fd);
	}
}

int	get_int_from_rgb(char	*buffer)
{
	char	**arr;
	int		i;
	int		n;
	int		tmp;

	i = 1;
	n = 0;
	arr = ft_split(buffer, ' ');
	if (!arr)
		// ERREUR
	while (arr[i] != NULL)
	{
		tmp = ft_atoi(arr[i]);
		if (tmp > 255 || tmp < 0)
			// ERREUR
		
	}
}
