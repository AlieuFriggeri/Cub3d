/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:03:41 by vgroux            #+#    #+#             */
/*   Updated: 2023/05/15 16:17:00 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map2[] = {
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 0, 0, 1, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 1, 0, 0, 1, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1
};

void	setplayer(t_cub *data)
{
	int	x;
	int	y;

	x = data->player.px;
	y = data->player.py;
	while (x < data->player.px + 10)
	{
		while (y < data->player.py + 10)
		{
			my_mlx_pixel_put(data, x - 5, y - 5, 0xFFF000);
			y++;
		}
		y = data->player.py;
		x++;
	}
	x = 0;
	y = 0;
	//draw_raycasting(data);
	if (checkHorizontalLines(data, 0) < checkVerticalLines(data, 0))
		checkHorizontalLines(data, 1);
	else
		checkVerticalLines(data, 1);
	mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
}

void	draw_raycasting(t_cub *data)
{
	int		n_ray;
	int		i;
	double	base_angle;

	n_ray = 1;
	i = 0;
	base_angle = data->player.pa;// - (n_ray * DEG);
	while (i < n_ray)
	{
		draw_line(data, base_angle);
		base_angle += 2 * DEG;
		i++;
	}
}

int	checkHorizontalLines(t_cub *data, int flag)
{
	// int r,
	int mx, my, mp, dof;
	float rx, ry, ra, xo, yo, atan;
	
	ra = data->player.pa;
	atan = -1 / tan(ra);
	dof = 0;
	data->mapx = 8;
	data->mapy = 8;
	if (ra > PI) //regarde en haut
	{
		ry = (((int)data->player.py>>6)<<6) - 0.0001;
		rx = (data->player.py - ry) * atan + data->player.px;
		yo = -64;
		xo = -yo * atan;
	}
	if (ra < PI) //regarde en bas
	{
		ry = (((int)data->player.py>>6)<<6) + 64;
		rx = (data->player.py - ry) * atan + data->player.px;
		yo = 64;
		xo = -yo * atan;
	}
	if ( ra == 0 || ra == PI)
	{
		rx = data->player.px;
		ry = data->player.py;
		dof = 8;
	}
	while (dof < 8)
	{
		mx = (int)rx>>6;
		my = (int)ry>>6;
		mp = my * data->mapx + mx;
		if (mp < data->mapx * data->mapy && map2[mp] == 1) // touche un mur
			dof = 8;
		else
		{
			rx += xo;
			ry += yo;
			dof += 1; // prochain ligne horizontale
		}
		//printf("%d\n", map2[mp]);
	}
	if (flag == 0)
		return (count_linetest(data, ra, rx, ry));
	else
	{
		printf("%f | %f\n", rx, ry);
		draw_linetest(data, ra, rx, ry);
	}
	return (0);
}

int	checkVerticalLines(t_cub *data, int flag)
{
	// int r,
	int mx, my, mp, dof;
	float rx, ry, ra, xo, yo, ntan;
	
	ra = data->player.pa;
	ntan = -tan(ra);
	dof = 0;
	data->mapx = 8;
	data->mapy = 8;
	if (ra > PI2 && ra < PI3) //regarde a gauche
	{
		rx = (((int)data->player.px>>6)<<6) - 0.0001;
		ry = (data->player.px - rx) * ntan + data->player.py;
		xo = -64;
		yo = -xo * ntan;
	}
	if (ra < PI2 || ra > PI3) //regarde en droite
	{
		rx = (((int)data->player.px>>6)<<6) + 64;
		ry = (data->player.px - rx) * ntan + data->player.py;
		xo = 64;
		yo = -xo * ntan;
	}
	if ( ra == 0 || ra == PI)
	{
		rx = data->player.px;
		ry = data->player.py;
		dof = 8;
	}
	while (dof < 8)
	{
		mx = (int)rx>>6;
		my = (int)ry>>6;
		mp = my * data->mapx + mx;
		if (mp < data->mapx * data->mapy && map2[mp] == 1) // touche un mur
			dof = 8;
		else
		{
			rx += xo;
			ry += yo;
			dof += 1; // prochain ligne horizontale
		}
		//printf("%d\n", map2[mp]);
	}
	if (flag == 0)
		return (count_linetest(data, ra, rx, ry));
	else
	{
		printf("%f | %f\t\t%f | %f\n", rx, ry, data->player.px, data->player.py);
		draw_linetest(data, ra, rx, ry);
	}
	return (0);
}

void	draw_linetest(t_cub *data, double angle, float rx, float ry)
{
	int		len;
	int		len2;
	double	startx;
	double	starty;

	len = 0;
	startx = data->player.px;
	starty = data->player.py;
	//printf(" %f %f\n", rx, ry);
	len2 = sqrt(pow( rx - startx, 2) + pow( ry - starty, 2));
	while (len < len2)
	{
		if (startx < WIDTH && starty < WIDTH && startx < HEIGHT && starty < HEIGHT)
		{
			my_mlx_pixel_put(data, startx, starty, 0xFFFFFF);
		}
		startx += cos(angle);
		starty += sin(angle);
		len++;
	}
	//my_mlx_pixel_put(data, rx, ry, 0x0000FF);
}

int	count_linetest(t_cub *data, double angle, float rx, float ry)
{
	int		len;
	int		len2;
	int		count;
	double	startx;
	double	starty;

	len = 0;
	count = 0;
	startx = data->player.px;
	starty = data->player.py;
	//printf(" %f %f\n", rx, ry);
	len2 = sqrt(pow( rx - startx, 2) + pow( ry - starty, 2));
	while (len < len2)
	{
		if (startx < WIDTH && starty < WIDTH && startx < HEIGHT && starty < HEIGHT)
		{
			//my_mlx_pixel_put(data, startx, starty, 0xFFFFFF);
			count++;
		}
		startx += cos(angle);
		starty += sin(angle);
		len++;
	}
	//my_mlx_pixel_put(data, rx, ry, 0x0000FF);
	return count;
}

void	draw_line(t_cub *data, double angle)
{
	int		len;
	double	startx;
	double	starty;

	len = 0;
	startx = data->player.px;
	starty = data->player.py;
	while (len < 400)
	{
		if (startx < WIDTH && starty < WIDTH && startx < HEIGHT && starty < HEIGHT)
			my_mlx_pixel_put(data, startx, starty, 0xFFFFFF);
		startx += cos(angle);
		starty += sin(angle);
		len++;
	}
}
