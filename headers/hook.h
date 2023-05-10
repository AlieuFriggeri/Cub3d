/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:22:09 by afrigger          #+#    #+#             */
/*   Updated: 2023/05/10 15:24:23 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOK_H
# define HOOK_H

# include "cub3d.h"

// hook.c
int		hook(int keycode, t_cub *data);
int		cub_exit(t_cub *data);
void	move_player(int keycode, t_cub *data);
void	rotate_player(int keycode, t_cub *data);

#endif
