/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checklines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:36:01 by vgroux            #+#    #+#             */
/*   Updated: 2023/06/12 13:05:33 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	check_horizontal_lines(t_cub *data, int flag)
{
	int		dof;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	atan;

	ra = data->player.pa2;
	atan = -1 / tan(ra);
	dof = 0;
	if (ra > PI)
	{
		ry = (((int)data->player.py >> 6) << 6) - 0.0001;
		rx = (data->player.py - ry) * atan + data->player.px;
		yo = -CUBSIZE;
		xo = -yo * atan;
	}
	else
	{
		ry = (((int)data->player.py >> 6) << 6) + CUBSIZE;
		rx = (data->player.py - ry) * atan + data->player.px;
		yo = CUBSIZE;
		xo = -yo * atan;
	}
	if (ra == 0 || ra == PI)
	{
		rx = data->player.px;
		ry = data->player.py;
		dof = data->mapx;
	}
	get_intersection(data, dof, xo, yo, &rx, &ry);
	if (flag == 0)
		return (dist_wallhit(data, rx, ry));
	else
	{
		data->player.flag = 0;
		draw_line3d(data, rx, ry);
	}
	return (0);
}

float	check_vertical_lines(t_cub *data, int flag)
{
	int		dof;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	ntan;

	ra = data->player.pa2;
	ntan = -tan(ra);
	dof = 0;
	if (ra > PI2 && ra < PI3)
	{
		rx = (((int)data->player.px >> 6) << 6) - 0.0001;
		ry = (data->player.px - rx) * ntan + data->player.py;
		xo = -CUBSIZE;
		yo = -xo * ntan;
	}
	else
	{
		rx = (((int)data->player.px >> 6) << 6) + CUBSIZE;
		ry = (data->player.px - rx) * ntan + data->player.py;
		xo = CUBSIZE;
		yo = -xo * ntan;
	}
	if (ra == 0 || ra == PI)
	{
		rx = data->player.px;
		ry = data->player.py;
		dof = data->mapy;
	}
	get_intersection(data, dof, xo, yo, &rx, &ry);
	if (flag == 0)
		return (dist_wallhit(data, rx, ry));
	else
	{
		data->player.flag = 1;
		draw_line3d(data, rx, ry);
	}
	return (0);
}

void	get_intersection(t_cub *data, int dof, float xo, float yo, float *rx, float *ry)
{
	int		mx;
	int		my;
	int		mp;

	while (dof < data->mapx)
	{
		mx = (int)*rx >> 6;
		my = (int)*ry >> 6;
		mp = my * data->mapx + mx;
		if (mp > 0 && mp < data->mapx * data->mapy && data->intmap[mp] == 1)
			dof = data->mapx;
		else
		{
			*rx += xo;
			*ry += yo;
			dof += 1;
		}
		data->player.lineH = (CUBSIZE * HEIGHT) / data->player.disT;
		if (data->player.lineH > HEIGHT)
			data->player.lineH = HEIGHT;
		data->player.lineO = HEIGHT / 2 - data->player.lineH / 2;
	}
}
