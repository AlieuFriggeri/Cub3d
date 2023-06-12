/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:08:25 by vgroux            #+#    #+#             */
/*   Updated: 2023/06/12 13:12:09 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texture(t_cub *data, char *av)
{
	char	**arg;

	if (av && av[0] != '\n')
	{
		arg = ft_split(av, ' ');
		if (!arg)
			printerror(data, "malloc error");
		if (ft_strncmp(arg[0], "NO", 2) == 0)
			get_texture(data, arg[1], NORTH);
		else if (ft_strncmp(arg[0], "SO", 2) == 0)
			get_texture(data, arg[1], SOUTH);
		else
			texture_scandal(data, arg);
		ft_free_arr(arg);
		free(av);
	}
	else if (av[0] == '\n')
		free(av);
}

void	texture_scandal(t_cub *data, char **arg)
{
	if (ft_strncmp(arg[0], "WE", 2) == 0)
		get_texture(data, arg[1], WEST);
	else if (ft_strncmp(arg[0], "EA", 2) == 0)
		get_texture(data, arg[1], EAST);
	else if (ft_strncmp(arg[0], "F", 1))
		get_color(data, &data->floor, arg[1]);
	else if (ft_strncmp(arg[0], "C", 1))
		get_color(data, &data->sky, arg[1]);
	else
		printerror(data, "Config issue");
}

void	get_color(t_cub *data, int *p, char *str)
{
	char	**arg;
	int		r;
	int		g;
	int		b;

	arg = ft_split(str, ',');
	if (!arg)
		printerror(data, "malloc error");
	r = ft_atoi(arg[0]);
	g = ft_atoi(arg[1]);
	b = ft_atoi(arg[2]);
	if (r > 255 || g > 255 || b > 255)
		printerror(data, "config error: color can't me higher than 255");
	else if (r < 0 || g < 0 || b < 0)
		printerror(data, "config error: color can't be negative");
	*p = encode_rgb(r, g, b);
	ft_free_arr(arg);
}
