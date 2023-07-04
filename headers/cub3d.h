/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:13:12 by afrigger          #+#    #+#             */
/*   Updated: 2023/07/04 15:47:39 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*	Personnal headers	*/
# include "../mlx_macos/mlx.h"
# include "../libft/libft.h"

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
# define PI2 1.57079632679
# define PI3 4.71238898038
# define DEG 0.0174533
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3
# define NBRAY 512

# define NBCARRE 8
# define CUBSIZE 64

typedef struct s_var
{
	int		dof;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	atan;
}	t_var;

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
	double		dist;
	double		lineh;
	double		lineo;
	int			r;
	int			spx;
	int			spy;
	int			ipx;
	int			ipx_add_xo;
	int			ipx_sub_xo;
	int			ipy;
	int			ipy_add_yo;
	int			ipy_sub_yo;
	float		last_rx;
	float		last_ra;
	float		last_ry;
	int			wall_dist;
	int			dwall_n;
	int			dwall_s;
	int			dwall_e;
	int			dwall_w;
	int			flag;
}	t_player;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			ed;
	int			sl;
	int			bpp;
	int			width;
	int			height;
}	t_img;

typedef struct s_cub{
	void		*mlx;
	void		*window;
	void		*img;
	char		*addr;
	int			ed;
	int			sl;
	int			bpp;
	t_player	player;
	int			mapx;
	int			mapy;
	t_img		wall[4];
	int			sky;
	int			floor;
	char		**map;
	int			*intmap;
	int			**mapnum;
	int			mapsize;
	int			mapstart;
	int			ax;
}	t_cub;

/* ----- MAIN ----- */
void	startpos(t_cub *data);
void	startangle(t_cub *data, char angle, int i, int j);
void	mapsizeint(t_cub *data);
int		countmapsize(int fd, t_cub *data);
char	**openmap(char *path, t_cub *data);
void	printerror(t_cub *data, char *str);
void	openmap_scandale(t_cub *data, char ***map, int size, char *path);

/* ----- DRAW ----- */
void	my_mlx_pixel_put(t_cub *data, int x, int y, int color);
void	drawsquare(int x, int y, t_cub *data, int type);
void	drawmap(t_cub *data);
void	render_square(t_cub *data, int x, int y, int i);
void	draw_line(t_cub *data, double angle);

/* ----- IMAGE ----- */
void	draw_sky(t_cub *data);
void	draw_floor(t_cub *data);
void	draw_image(t_cub *data);

/* ----- PLAYER ----- */
void	setplayer(t_cub *data);
void	draw_raycasting(t_cub *data);
float	check_horizontal_lines(t_cub *data, int flag);
void	get_intersection(t_cub *data, t_var *var);
float	check_vertical_lines(t_cub *data, int flag);
float	dist_wallhit(t_cub *data, float rx, float ry);
void	draw_line3d(t_cub *data, float rx, float ry);
void	check_angle(t_cub *data);
void	setmap(t_cub *data);
void	alloc_intmap(t_cub *data);
void	ra_equal_pi(t_cub *data, t_var *var);
int		ft_scandale(t_cub *data, t_var *var, int flag, int flag2);

/* ----- HOOK ----- */
int		cub_exit(t_cub *data);
void	check_angle(t_cub *data);
void	rotate_player(int keycode, t_cub *data);
void	move_player(int keycode, t_cub *data);
int		hook(int keycode, t_cub *data);
void	check_collision(t_cub *data);

/* ----- SPECIAL OS ----- */
void	add_hook(t_cub *data);

/* ----- INIT ----- */
void	init(t_cub *data, char *av);
void	init_null(t_cub *data);
void	check_color(t_cub *data);
int		countmap_scandale(int fd, char *res, int x);
void	setmap_scandale(t_cub *data, int i, int j);
void	setmap_scandale2(t_cub *data, int i, int j);

/* ----- TEXTURE ----- */
int		get_texture(t_cub *data, char *path, int wall);
int		get_color_from_texture(t_cub *data, int x, int y, int wall);
void	print_texture(t_cub *data, double ratiox, int y, int wall);
void	select_texture(t_cub *data, float rx, float ry, int y);
void	texture(t_cub *data, char *av);
void	get_color(t_cub *data, int *p, char *str);
int		encode_rgb(int r, int g, int b);
void	texture_scandal(t_cub *data, char **arg);

/*------ PARSER -------*/
int		check_col(t_cub *data);
int		check_line(t_cub *data);
void	setmapnum(t_cub *data);
int		extra_map_check(t_cub *data);

#endif
