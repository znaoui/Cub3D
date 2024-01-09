/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 19:39:58 by cdudzik           #+#    #+#             */
/*   Updated: 2023/01/30 18:09:50 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "cub3d.h"
#include "keys.h"
#include "mlx.h"

static void	update_camera(t_data *d)
{
	double	dir_x;
	double	plane_x;
	double	i;

	i = 0;
	if (d->keys.rotate_left_pressed)
		i = 1;
	else if (d->keys.rotate_right_pressed)
		i = -1;
	if (i)
	{
		if (DEBUG)
			printf("plane(%f, %f) dir(%f,%f)\n", d->player.plane.x,
				d->player.plane.y, d->player.dir.x, d->player.dir.y);
		dir_x = d->player.dir.x;
		plane_x = d->player.plane.x;
		d->player.dir.x = d->player.dir.x * cos(d->rot_speed * i)
			- d->player.dir.y * sin(d->rot_speed * i);
		d->player.dir.y = dir_x * sin(d->rot_speed * i)
			+ d->player.dir.y * cos(-d->rot_speed * i);
		d->player.plane.x = d->player.plane.x * cos(d->rot_speed * i)
			- d->player.plane.y * sin(d->rot_speed * i);
		d->player.plane.y = plane_x * sin(d->rot_speed * i)
			+ d->player.plane.y * cos(d->rot_speed * i);
	}
}

static void	update_horizontal_pos(t_data *d)
{
	if (d->keys.left_pressed)
	{
		if (DEBUG)
			printf("pos(%d,%d)\n", (int)d->player.pos.x, (int)d->player.pos.y);
		if (!d->map->grid[(int)(d->player.pos.x
				- d->player.plane.x * d->move_speed * 2)]
					[(int)(d->player.pos.y)])
			d->player.pos.x -= d->player.plane.x * d->move_speed;
		if (!d->map->grid[(int)(d->player.pos.x)][(int)(d->player.pos.y
				- d->player.plane.y * d->move_speed * 2)])
			d->player.pos.y -= d->player.plane.y * d->move_speed;
	}
	if (d->keys.right_pressed)
	{
		if (DEBUG)
			printf("pos(%d,%d)\n", (int)d->player.pos.x, (int)d->player.pos.y);
		if (!d->map->grid[(int)(d->player.pos.x
				+ d->player.plane.x * d->move_speed)][(int)(d->player.pos.y)])
			d->player.pos.x += d->player.plane.x * d->move_speed;
		if (!d->map->grid[(int)(d->player.pos.x)][(int)(d->player.pos.y
				+ d->player.plane.y * d->move_speed)])
			d->player.pos.y += d->player.plane.y * d->move_speed;
	}
}

int	update_player_position(t_data *d)
{
	if (d->keys.forward_pressed)
	{
		if (DEBUG)
			printf("pos(%d,%d)\n", (int)d->player.pos.x, (int)d->player.pos.y);
		if (!d->map->grid[(int)(d->player.pos.x
				+ d->player.dir.x * d->move_speed)][(int)(d->player.pos.y)])
			d->player.pos.x += d->player.dir.x * d->move_speed;
		if (!d->map->grid[(int)(d->player.pos.x)][(int)(d->player.pos.y
				+ d->player.dir.y * d->move_speed)])
			d->player.pos.y += d->player.dir.y * d->move_speed;
	}
	if (d->keys.backward_pressed)
	{
		if (DEBUG)
			printf("pos(%d,%d)\n", (int)d->player.pos.x, (int)d->player.pos.y);
		if (!d->map->grid[(int)(d->player.pos.x
				- d->player.dir.x * d->move_speed * 2)][(int)(d->player.pos.y)])
			d->player.pos.x -= d->player.dir.x * d->move_speed;
		if (!d->map->grid[(int)(d->player.pos.x)][(int)(d->player.pos.y
				- d->player.dir.y * d->move_speed * 2)])
			d->player.pos.y -= d->player.dir.y * d->move_speed;
	}
	update_horizontal_pos(d);
	update_camera(d);
	return (0);
}

int	key_pressed_hook(int keycode, t_data *data)
{
	if (DEBUG)
		printf("[DEBUG] key_press %d\n", keycode);
	if (keycode == KEY_W)
		data->keys.forward_pressed = 1;
	else if (keycode == KEY_S)
		data->keys.backward_pressed = 1;
	else if (keycode == KEY_A)
		data->keys.left_pressed = 1;
	else if (keycode == KEY_D)
		data->keys.right_pressed = 1;
	else if (keycode == KEY_ARROW_LEFT)
		data->keys.rotate_left_pressed = 1;
	else if (keycode == KEY_ARROW_RIGHT)
		data->keys.rotate_right_pressed = 1;
	else if (keycode == KEY_ESC)
		mlx_loop_end(data->mlx);
	return (0);
}

int	key_released_hook(int keycode, t_data *data)
{
	if (DEBUG)
		printf("[DEBUG] key_release %d\n", keycode);
	if (keycode == KEY_W)
		data->keys.forward_pressed = 0;
	else if (keycode == KEY_S)
		data->keys.backward_pressed = 0;
	else if (keycode == KEY_A)
		data->keys.left_pressed = 0;
	else if (keycode == KEY_D)
		data->keys.right_pressed = 0;
	else if (keycode == KEY_ARROW_LEFT)
		data->keys.rotate_left_pressed = 0;
	else if (keycode == KEY_ARROW_RIGHT)
		data->keys.rotate_right_pressed = 0;
	return (0);
}
