/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:11:46 by cdudzik           #+#    #+#             */
/*   Updated: 2023/01/21 18:38:17 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	init_positions(t_data *d)
{
	if (d->map->orientation_start == START_NORTH)
	{
		d->player.dir.x = -1;
		d->player.plane.y = 0.66;
	}
	else if (d->map->orientation_start == START_SOUTH)
	{
		d->player.dir.x = 1;
		d->player.plane.y = -0.66;
	}
	else if (d->map->orientation_start == START_EAST)
	{
		d->player.dir.y = 1;
		d->player.plane.x = 0.66;
	}
	else
	{
		d->player.dir.y = -1;
		d->player.plane.x = -0.66;
	}
}
