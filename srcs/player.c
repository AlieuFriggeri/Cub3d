/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:03:41 by vgroux            #+#    #+#             */
/*   Updated: 2023/05/16 14:34:52 by afrigger         ###   ########.fr       */
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
	int r = 0;
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
	//printf("in setplayer\n");
	//draw_raycasting(data);
	data->player.pa2 = data->player.pa - DEG * 30;
	while (r < 60)
	{
		data->player.r = r;
		if (checkHorizontalLines(data, 0) < checkVerticalLines(data, 0))
		{
			data->player.disT = checkHorizontalLines(data, 0);
			checkHorizontalLines(data, 1);
		}
		else
		{
			data->player.disT = checkVerticalLines(data, 0);
			checkVerticalLines(data, 1);
		}
		data->player.pa2 += DEG;
		r++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
	//printf("out setplayer\n");
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
	//int r;
	int mx, my, mp, dof;
	float rx, ry, ra, xo, yo, atan;
	
	ra = data->player.pa2;
	// if (ra < 0)
	// 	ra += 2 * PI;
	// else if (ra > 2 * PI)
	// 	ra -= 2 * PI;
	//r = 0;
	// while (r < 60)
	// {
		atan = -1 / tan(ra);
		dof = 0;
		data->mapx = 8;
		data->mapy = 8;
		//printf("in horizontal\n");
		if (ra > PI) //regarde en haut
		{
			ry = (((int)data->player.py>>6)<<6) - 0.0001;
			rx = (data->player.py - ry) * atan + data->player.px;
			yo = -64;
			xo = -yo * atan;
			//printf("in horizontal 0\n");
		}
		else if (ra < PI) //regarde en bas
		{
			ry = (((int)data->player.py>>6)<<6) + 64;
			rx = (data->player.py - ry) * atan + data->player.px;
			yo = 64;
			xo = -yo * atan;
			//printf("in horizontal 1\n");
		}
		else if ( ra == 0 || ra == PI)
		{
			rx = data->player.px;
			ry = data->player.py;
			dof = 8;
			//printf("in horizontal 2\n");
		}
		while (dof < 8)
		{
			mx = (int)rx>>6;
			my = (int)ry>>6;
			mp = my * data->mapx + mx;
			if (mp > 0 && mp < data->mapx * data->mapy && map2[mp] == 1) // touche un mur
				dof = 8;
			else
			{
				rx += xo;
				ry += yo;
				dof += 1; // prochain ligne horizontale
			}
			//printf("%d\n", map2[mp]);
			//printf("in horizontal 3\n");
			data->player.lineH = (64 * HEIGHT) / data->player.disT;
			if (data->player.lineH > HEIGHT)
				data->player.lineH = HEIGHT;
		}
		if (flag == 0)
			return (count_linetest(data, ra, rx, ry));
		else
		{
			//printf("%f | %f\n", rx, ry);
			draw_linetest(data, ra, rx, ry);
			draw_line3d(data);
		}
	// 	r++;
	// 	ra += DEG;
	// }
	//printf("OUT horizontal\n");
	return (0);
}

int	checkVerticalLines(t_cub *data, int flag)
{
	//int r;
	int mx, my, mp, dof;
	float rx, ry, ra, xo, yo, ntan;
	
	ra = data->player.pa2;
	//r = 0;
	// while (r < 60)
	// {
		ntan = -tan(ra);
		dof = 0;
		data->mapx = 8;
		data->mapy = 8;
		//printf("in vertical\n");
		if (ra > PI2 && ra < PI3) //regarde a gauche
		{
			rx = (((int)data->player.px>>6)<<6) - 0.0001;
			ry = (data->player.px - rx) * ntan + data->player.py;
			xo = -64;
			yo = -xo * ntan;
			//printf("in vertical 0\n");
		}
		if (ra < PI2 || ra > PI3) //regarde a droite
		{
			rx = (((int)data->player.px>>6)<<6) + 64;
			ry = (data->player.px - rx) * ntan + data->player.py;
			xo = 64;
			yo = -xo * ntan;
			//printf("in vertical 1\n");
		}
		if ( ra == 0 || ra == PI)
		{
			rx = data->player.px;
			ry = data->player.py;
			dof = 8;
			//printf("in vertical 2\n");
		}
		while (dof < 8)
		{
			//printf("in vertical 3\n");
			mx = (int)rx>>6;
			my = (int)ry>>6;
			mp = my * data->mapx + mx;
			if (mp > 0 && mp < data->mapx * data->mapy && map2[mp] == 1) // touche un mur
				dof = 8;
			else
			{
				rx += xo;
				ry += yo;
				dof += 1; // prochain ligne horizontale
			}
			//printf("%d\n", map2[mp]);
			data->player.lineH = (64 * HEIGHT) / data->player.disT;
			if (data->player.lineH > HEIGHT)
				data->player.lineH = HEIGHT;
		}
		if (flag == 0)
			return (count_linetest(data, ra, rx, ry));
		else
		{
			//printf("%f | %f\t\t%f | %f\n", rx, ry, data->player.px, data->player.py);
			draw_linetest(data, ra, rx, ry);
			draw_line3d(data);
		}
	//	r++;
	//	ra += DEG;
	//}
	//printf("OUT vertical\n");
	return (0);
}

void	draw_line3d(t_cub *data)
{
	int y;
	int x;
	int x2;

	x = data->player.r * 8 + WIDTH / 2;
	x2 = x+8;
	while (x < x2)
	{
		y = 0;
		while (y < data->player.lineH)
		{
			my_mlx_pixel_put(data, x, y, 0xFF0000);
			y++;
		}
		x++;
	}
}

void	draw_linetest(t_cub *data, double angle, float rx, float ry)
{
	int		len;
	int		len2;
	double	startx;
	double	starty;
	// int i;
	// int nb_ray;
	// i = 0;
	// nb_ray = 1;
		len = 0;
		startx = data->player.px;
		starty = data->player.py;
		//printf(" %f %f\n", rx, ry);
		len2 = sqrt((pow( rx - startx, 2) + pow( ry - starty, 2)));
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
