/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:38:10 by vgroux            #+#    #+#             */
/*   Updated: 2023/06/07 17:23:42 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_collision(t_cub *data)
{
	int	r;
	int	dist;

	r = 0;
	data->player.pa2 = data->player.pa - (DEG * 180);
	while (r < 4)
	{
		if (check_horizontal_lines(data, 0) < check_vertical_lines(data, 0))
			dist = check_horizontal_lines(data, 0);
		else
			dist = check_vertical_lines(data, 0);
		if (r == 0)
			data->player.dwall_s = dist;
		if (r == 1)
			data->player.dwall_w = dist;
		if (r == 2)
			data->player.dwall_n = dist;
		if (r == 3)
			data->player.dwall_e = dist;
		data->player.pa2 += DEG * 90;
		r++;
	}
}
