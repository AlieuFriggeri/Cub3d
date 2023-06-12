/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checklines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:36:01 by vgroux            #+#    #+#             */
/*   Updated: 2023/06/12 17:42:24 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	check_horizontal_lines(t_cub *data, int flag)
{
	t_var	var;

	var.ra = data->player.pa2;
	var.atan = -1 / tan(var.ra);
	var.dof = 0;
	if (var.ra > PI)
	{
		var.ry = (((int)data->player.py >> 6) << 6) - 0.0001;
		var.rx = (data->player.py - var.ry) * var.atan + data->player.px;
		var.yo = -CUBSIZE;
		var.xo = -var.yo * var.atan;
	}
	else
	{
		var.ry = (((int)data->player.py >> 6) << 6) + CUBSIZE;
		var.rx = (data->player.py - var.ry) * var.atan + data->player.px;
		var.yo = CUBSIZE;
		var.xo = -var.yo * var.atan;
	}
	return (ft_scandale(data, &var, flag, 0));
}

int	ft_scandale(t_cub *data, t_var *var, int flag, int flag2)
{
	ra_equal_pi(data, var);
	get_intersection(data, var);
	if (flag == 0)
		return (dist_wallhit(data, var->rx, var->ry));
	else
	{
		data->player.flag = flag2;
		draw_line3d(data, var->rx, var->ry);
	}
	return (0);
}

float	check_vertical_lines(t_cub *data, int flag)
{
	t_var	var;

	var.ra = data->player.pa2;
	var.atan = -tan(var.ra);
	var.dof = 0;
	if (var.ra > PI2 && var.ra < PI3)
	{
		var.rx = (((int)data->player.px >> 6) << 6) - 0.0001;
		var.ry = (data->player.px - var.rx) * var.atan + data->player.py;
		var.xo = -CUBSIZE;
		var.yo = -var.xo * var.atan;
	}
	else
	{
		var.rx = (((int)data->player.px >> 6) << 6) + CUBSIZE;
		var.ry = (data->player.px - var.rx) * var.atan + data->player.py;
		var.xo = CUBSIZE;
		var.yo = -var.xo * var.atan;
	}
	return (ft_scandale(data, &var, flag, 1));
}

void	ra_equal_pi(t_cub *data, t_var *var)
{
	if (var->ra == 0 || var->ra == PI)
	{
		var->rx = data->player.px;
		var->ry = data->player.py;
		var->dof = data->mapy;
	}
}

void	get_intersection(t_cub *data, t_var *var)
{
	int		mx;
	int		my;
	int		mp;

	while (var->dof < data->mapx)
	{
		mx = (int)var->rx >> 6;
		my = (int)var->ry >> 6;
		mp = my * data->mapx + mx;
		if (mp > 0 && mp < data->mapx * data->mapy && (data->intmap[mp] == 1
			|| data->intmap[mp] == 2))
			var->dof = data->mapx;
		else
		{
			var->rx += var->xo;
			var->ry += var->yo;
			var->dof += 1;
		}
		data->player.lineh = (CUBSIZE * HEIGHT) / data->player.dist;
		if (data->player.lineh > HEIGHT)
			data->player.lineh = HEIGHT;
		data->player.lineo = HEIGHT / 2 - data->player.lineh / 2;
	}
}
