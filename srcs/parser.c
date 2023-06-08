/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:43:18 by vgroux            #+#    #+#             */
/*   Updated: 2023/06/08 17:42:34 by afrigger         ###   ########.fr       */
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
		if (check_first_line(data) != 0)
			return (123);
		if (ft_isspace(data->map[i][j]) == 1)
			if (check_map_space(data, i, j) != 0)
				return (123);
		if (check_map_first(data, i, j) != 0)
			return (123);
		if (check_map_last(data, i ,j))
			return (123);
		i++;
		j = 0;
	}
	return (0);
}

int	check_map_space(t_cub *data, int i, int j)
{	
	while (ft_isspace(data->map[i][j]) == 1)
	{
		printf("space\n");
		if (data->map[i - 1][j] == '0' || data->map[i + 1][j] == '0')
			return(123);
		if ((data->map[i][j + 1] == '0' && data->map[i][j] != '1') || (data->map[i][j - 1] == '0' && j != 0))
			return (123);
		j++;
	}
	return(0);
}

int	check_map_first(t_cub *data, int i, int j)
{printf("first\n");
	while(ft_isspace(data->map[i][j] == 1))
		j++;
	if (data->map[i][j] == '0')
		return (123);
	return (0);
}

int check_map_last(t_cub *data, int i, int j)
{printf("last\n");
	j = ft_strlen(data->map[i]);
	while (ft_isspace(data->map[i][j]) == 1)
	{
		if (data->map[i - 1][j] == '0' || data->map[i + 1][j] == '0')
			return (123);
		j--;
	}
	if (data->map[i][j] == '0')
		return (123);
	return (0);
}

int check_first_line(t_cub *data)
{printf("firstline\n");
	int i;
	int j;

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