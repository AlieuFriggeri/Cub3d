/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:13:12 by afrigger          #+#    #+#             */
/*   Updated: 2023/05/17 13:45:54 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*	Personnal headers	*/
# include "../mlx_macos/mlx.h"
# include "../libft/libft.h"
# include "map.h"
# include "hook.h"

/*	Official headers	*/
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# define WIDTH 1024
# define HEIGHT 512
# define PI 3.1415926535
# define PI2 PI / 2
# define PI3 3 * PI2
# define DEG 0.0174533
# define BLUE_COLOR 0x87CEEB
# define GREY_COLOR 0x808080

typedef struct s_player{
	double		px;
	double		py;
	double		pdx;
	double		pdy;
	double		pa;
	double		pa2;
	double		m;
	double		n;
	double		startx;
	double		starty;
	double		endx;
	double		endy;
	double		disT;
	double		lineH;
	double		lineO;
	int			r;
}	t_player;

typedef struct s_cub{
	void		*mlx;
	void		*window;
	void		*img;
	char		*addr;
	int			endian;
	int			sizeline;
	int			bpp;
	t_player	player;
	int			mapx;
	int			mapy;
}	t_cub;

/* ----- MAIN ----- */
int		main(void);
void	drawmap(t_cub *data);
void	fill_all(t_cub *data);

/* ----- DRAW ----- */
void	my_mlx_pixel_put(t_cub *data, int x, int y, int color);
void	drawsquare(int x, int y, t_cub *data, int type);

/* ----- IMAGE ----- */
void	draw_sky(t_cub *data);
void	draw_floor(t_cub *data);
void	draw_image(t_cub *data);

/* ----- PLAYER ----- */
void	setplayer(t_cub *data);
void	draw_raycasting(t_cub *data);
void	draw_line(t_cub *data, double angle);
int	checkHorizontalLines(t_cub *data, int flag);
void		draw_linetest(t_cub *data, double angle, float rx, float ry);
int	checkVerticalLines(t_cub *data, int flag);
int		count_linetest(t_cub *data, double angle, float rx, float ry);
void	draw_line3d(t_cub *data);
void	check_angle(t_cub *data);

/* ----- HOOK ----- */
int		hook(int keycode, t_cub *data);
int		cub_exit(t_cub *data);
void	move_player(int keycode, t_cub *data);
void	rotate_player(int keycode, t_cub *data);

#endif
