/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:43:18 by vgroux            #+#    #+#             */
/*   Updated: 2023/06/12 18:04:51 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_col(t_cub *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->mapy)
	{
		j = 0;
		while (j < data->mapy - 1 && data->mapnum[j][i] == 3)
			j++;
		if (data->mapnum[j][i] != 1)
			return (0);
		j = data->mapy - 1;
		while (j > 0 && data->mapnum[j][i] == 3)
			j--;
		if (data->mapnum[j][i] != 1)
			return (0);
		i++;
	}
	return (1);
}

int	check_line(t_cub *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->mapy)
	{
		j = 0;
		while (j < data->mapx - 1 && data->mapnum[i][j] == 3)
			j++;
		if (data->mapnum[i][j] != 1)
			return (0);
		j = data->mapx - 1;
		while (j > 0 && data->mapnum[i][j] == 3)
			j--;
		if (data->mapnum[i][j] != 1)
			return (0);
		i++;
	}
	return (1);
}

void	setmapnum(t_cub *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	alloc_intmap(data);
	mapsizeint(data);
	data->mapnum = malloc(sizeof(int *) * data->mapy);
	while (i < data->mapy)
	{
		data->mapnum[i] = malloc(sizeof(int) * data->mapx);
		i++;
	}
	i = 0;
	while (data->map[i])
	{
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
				data->mapnum[i][j] = 1;
			else if (data->map[i][j] == '0')
				data->mapnum[i][j] = 0;
			else if (ft_isspace(data->map[i][j]) == 1)
				data->mapnum[i][j] = 3;
			else if (data->map[i][j] >= 'A' && data->map[i][j] <= 'Z')
				data->mapnum[i][j] = 0;
			else
			{
				perror("pd\n");
				exit(123);
			}
			j++;
		}
		while (j < data->mapx)
		{
			data->mapnum[i][j] = 3;
			j++;
		}
		j = 0;
		i++;
	}
}

int	extra_map_check(t_cub *data)
{
	int	h;
	int	w;

	h = 1;
	w = 1;
	while (h < data->mapy - 1)
	{
		w = 1;
		while (w < data->mapx - 1)
		{
			if (data->mapnum[h][w] == 0 && (data->mapnum[h - 1][w] == 3
				|| data->mapnum[h + 1][w] == 3 ||data->mapnum[h]
					[w - 1] == 3 || data->mapnum[h][w + 1] == 3))
				return (0);
			w++;
		}
		h++;
	}
	return (1);
}