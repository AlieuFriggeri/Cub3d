/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:22:09 by afrigger          #+#    #+#             */
/*   Updated: 2023/03/16 12:57:12 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOK_H
#define HOOK_H

#include "cub3d.h"

// hook.c
int		hook(int keycode, t_cub *data);
int		cub_exit(t_cub *data);
void	move_player(int keycode ,t_cub *data);

#endif