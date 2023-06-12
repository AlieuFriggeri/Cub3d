/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:43:18 by vgroux            #+#    #+#             */
/*   Updated: 2023/06/12 17:59:21 by vgroux           ###   ########.fr       */
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
