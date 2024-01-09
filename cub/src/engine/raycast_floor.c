/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 19:34:36 by cdudzik           #+#    #+#             */
/*   Updated: 2023/01/30 18:23:49 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"

void	draw_floor_ceiling(t_data *data, t_raycast_vars *v)
{
	int			i;

	v->coords.y = v->draw_end;
	if (v->coords.y < 0)
		v->coords.y = SCREEN_HEIGHT;
	while (++v->coords.y < SCREEN_HEIGHT)
	{
		i = data->map->textures->floor[0];
		data->screen.addr[v->coords.y * SCREEN_WIDTH + v->coords.x] = i;
		i = (SCREEN_HEIGHT - v->coords.y - 1) * SCREEN_WIDTH + v->coords.x;
		data->screen.addr[i] = data->map->textures->ceiling[0];
	}
}
