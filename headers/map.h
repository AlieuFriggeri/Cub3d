/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:47:19 by vgroux            #+#    #+#             */
/*   Updated: 2023/05/10 15:49:25 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct s_map
{
	char	**map;
	int		color_sky;
	int		color_floor;
	char	*mesh_north;
	char	*mesh_south;
	char	*mesh_west;
	char	*mesh_east;
}	t_map;

#endif
