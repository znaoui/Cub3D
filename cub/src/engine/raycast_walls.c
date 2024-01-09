/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 19:37:15 by cdudzik           #+#    #+#             */
/*   Updated: 2023/01/21 18:38:17 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"

int	max(int a, int b);

static int	get_texture(t_raycast_vars *vars)
{
	int	texture;

	texture = 0;
	if (vars->side == 0 && vars->ray_dir.x >= 0)
		texture = 0;
	if (vars->side == 0 && vars->ray_dir.x < 0)
		texture = 1;
	if (vars->side == 1 && vars->ray_dir.y < 0)
		texture = 2;
	if (vars->side == 1 && vars->ray_dir.y >= 0)
		texture = 3;
	return (texture);
}

static void	set_next_step_dir(t_data *data, t_raycast_vars *vars)
{
	if (vars->ray_dir.x < 0)
	{
		vars->step.x = -1;
		vars->side_dist.x = (data->player.pos.x - vars->map.x)
			* vars->delta_dist.x;
	}
	else
	{
		vars->step.x = 1;
		vars->side_dist.x = (vars->map.x + 1.0 - data->player.pos.x)
			* vars->delta_dist.x;
	}
	if (vars->ray_dir.y < 0)
	{
		vars->step.y = -1;
		vars->side_dist.y = (data->player.pos.y - vars->map.y)
			* vars->delta_dist.y;
	}
	else
	{
		vars->step.y = 1;
		vars->side_dist.y = (vars->map.y + 1.0 - data->player.pos.y)
			* vars->delta_dist.y;
	}
}

void	dda(t_data *data, t_raycast_vars *v)
{
	set_next_step_dir(data, v);
	while (1)
	{
		if (v->side_dist.x < v->side_dist.y)
		{
			v->side_dist.x += v->delta_dist.x;
			v->map.x += v->step.x;
			v->side = 0;
		}
		else
		{
			v->side_dist.y += v->delta_dist.y;
			v->map.y += v->step.y;
			v->side = 1;
		}
		if (data->map->grid[v->map.x][v->map.y] == WALL)
			break ;
	}
}

void	cast_wall(t_data *data, t_raycast_vars *v, t_point_i *tex,
	int line_height)
{
	int		y;
	double	step;
	double	texture_position;
	int		texture_y;
	int		texture_num;

	y = v->draw_start;
	step = 1.0 * TEXTURE_HEIGHT / line_height;
	texture_position = (v->draw_start - SCREEN_HEIGHT / 2
			+ line_height / 2) * step;
	texture_num = get_texture(v);
	while (y < v->draw_end)
	{
		texture_y = (int)texture_position & (TEXTURE_HEIGHT - 1);
		texture_position += step;
		data->screen.addr[y * SCREEN_WIDTH + v->coords.x]
			= data->textures[texture_num][TEXTURE_HEIGHT * texture_y + tex->x];
		y++;
	}
}

double	draw_wall(t_data *data, t_raycast_vars *v)
{
	int			line_height;
	double		wall_x;
	t_point_i	texture;

	line_height = (int)(SCREEN_HEIGHT / v->perp_wall_dist);
	v->draw_start = max(0, -line_height / 2 + SCREEN_HEIGHT / 2);
	v->draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (v->draw_end >= SCREEN_HEIGHT)
		v->draw_end = SCREEN_HEIGHT - 1;
	if (v->side == 0)
		wall_x = data->player.pos.y + v->perp_wall_dist * v->ray_dir.y;
	else
		wall_x = data->player.pos.x + v->perp_wall_dist * v->ray_dir.x;
	wall_x -= floor(wall_x);
	texture.x = (int)(wall_x * (double)TEXTURE_WIDTH);
	if ((v->side == 0 && v->ray_dir.x > 0)
		|| (v->side == 1 && v->ray_dir.y < 0))
		texture.x = TEXTURE_WIDTH - texture.x - 1;
	cast_wall(data, v, &texture, line_height);
	return (wall_x);
}
