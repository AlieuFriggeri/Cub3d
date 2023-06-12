/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:43:18 by vgroux            #+#    #+#             */
/*   Updated: 2023/06/12 17:32:36 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map(t_cub *data)
{
	int i;
	int j;
	i = 1;
	j = 0;
	while (data->map[i])
	{
		while (data->map[i][j])
		{
			if (check_map_first(data, i, j))
				return (123);
			if(check_map_last(data, i, j))
				return (123);
			if (check_map_space(data, i, j))
				return (123);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	check_map_space(t_cub *data, int i, int j)
{	
	while (ft_isspace(data->map[i][j]) == 1)
	{
		if (data->map[i - 1][j] == '0' || data->map[i + 1][j] == '0')
			return (123);
		if ((data->map[i][j + 1] == '0' && data->map[i][j] != '1') || (data->map[i][j - 1] == '0' && j != 0))
			return (123);
		j++;
	}
	j = ft_strlen(data->map[i]);
	while (ft_isspace(data->map[i][j]) == 1)
	{
		if (data->map[i - 1][j] == '0' || data->map[i + 1][j] == '0')
			return (123);
		if ((data->map[i][j + 1] == '0' && data->map[i][j] != '1') || (data->map[i][j - 1] == '0' && j != 0))
			return (123);
		j--;
	}
	return (0);
}

int	check_map_first(t_cub *data, int i, int j)
{
	while (ft_isspace(data->map[i][j] == 1))
		j++;
	if (data->map[i][j] == '0')
		return (123);
	return (0);
}

int	check_map_last(t_cub *data, int i, int j)
{
	j = ft_strlen(data->map[i]) - 1;
	while (data->map[i][j] != '1')
	{
		if (data->map[i - 1])
			if (data->map[i - 1][j] == '0')
				return (123);
		if (data->map[i + 1])
			if (data->map[i + 1][j] == '0')
				return (123);
		j--;
	}
	if (data->map[i][j] == '0')
		return (123);
	return (0);
}

int	check_first_line(t_cub *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ft_isspace(data->map[i][j]))
		j++;
	while (data->map[i][j])
	{
		if (data->map[i][j] == '0')
			return (123);
		j++;
	}
	return (0);
}

void	printmap(t_cub *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	printf("mapx: %d\t\tmapy: %d\tmapsize: %d\n\n", data->mapx, data->mapy, data->mapsize);
	while (y < data->mapy)
	{
		x = 0;
		while (x < data->mapx)
		{
			printf("%d", data->intmap[y * data->mapy + x]);
			x++;
		}
		printf("\n");
		y++;		
	}
}
/* int	check_spawn(t_cub *data)
{
	int	i;
	int	j;
	int	n;

	i = 0;player
		j = 0;
		while (j < data->mapy)
		{
			if (player->worldmap[i][j] == 7)
			{
				player->pos.x = i;
				player->pos.y = j;
				player->worldmap[i][j] = 0;
				n += 1;
			}
			j++;
		}
		i++;
	}
	return (n);
} */

int	check_col(t_cub *data)
{
	int	x;
	int	y;

	y = 0;
	printmap(data);
	while (y < data->mapy)
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
	// int	i;
	// int	j;

	// i = 0;
	// j = 0;
	// while (i < data->mapx - 1)
	// {
	// 	j = 0;
	// 	while (j < data->mapy - 1 && !data->map[i][j])
	// 		j++;
	// 	if (data->map[i][j] != '1')
	// 		return (0);
	// 	j = data->mapy - 1;
	// 	while (j > 0 && !data->map[i][j])
	// 		j--;
	// 	if (data->map[i][j] != '1')
	// 		return (0);
	// 	i++;
	// }
	// return (1);

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


void	setmapnum(t_cub * data)
{
	int i;
	int j;
	i = 0;
	j = 0;
	//printf("%d\n", data->mapy);
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
		{//printf("%d\t%d\t\n", i, j);
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
		//printf("salut\n");
	}
}