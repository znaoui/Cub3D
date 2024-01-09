/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:07:07 by cdudzik           #+#    #+#             */
/*   Updated: 2023/02/02 16:28:52 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"
#include "mlx.h"
#include <math.h>
#include "libft.h"

int		load_textures(t_data *data);
int		dda(t_data *data, t_raycast_vars *vars);
double	draw_wall(t_data *data, t_raycast_vars *vars);
int		update_player_position(t_data *data);
void	draw_floor_ceiling(t_data *d, t_raycast_vars *v, double l);
int		key_pressed_hook(int keycode, t_data *data);
int		key_released_hook(int keycode, t_data *data);
void	init_positions(t_data *d);

void	init_loop_vars(t_data *data, t_raycast_vars *vars)
{
	double	camera_x;

	camera_x = 2 * vars->coords.x / (double)SCREEN_WIDTH - 1;
	vars->ray_dir.x = data->player.dir.x + data->player.plane.x * camera_x;
	vars->ray_dir.y = data->player.dir.y + data->player.plane.y * camera_x;
	vars->map.x = (int)data->player.pos.x;
	vars->map.y = (int)data->player.pos.y;
	vars->delta_dist.x = fabs(1 / vars->ray_dir.x);
	vars->delta_dist.y = fabs(1 / vars->ray_dir.y);
	ft_memset(&vars->side_dist, 0, sizeof(t_point));
	vars->draw_start = 0;
	vars->draw_end = 0;
	vars->side = 0;
}

void	raycast(t_data *data)
{
	t_raycast_vars	v;
	double			wall_x;

	v.coords.x = -1;
	while (++v.coords.x < SCREEN_WIDTH)
	{
		init_loop_vars(data, &v);
		dda(data, &v);
		if (v.side == 0)
			v.perp_wall_dist = (v.map.x - data->player.pos.x
					+ (1 - v.step.x) / 2) / v.ray_dir.x;
		else
			v.perp_wall_dist = (v.map.y - data->player.pos.y
					+ (1 - v.step.y) / 2) / v.ray_dir.y;
		wall_x = draw_wall(data, &v);
		draw_floor_ceiling(data, &v, wall_x);
	}
}

int	render_next_frame(t_data *data)
{
	raycast(data);
	mlx_put_image_to_window(data->mlx, data->win, data->screen.img, 0, 0);
	update_player_position(data);
	return (0);
}

int	init_data(t_data *data, t_map *map)
{
	data->win = NULL;
	data->textures = NULL;
	data->map = map;
	data->player.pos.x = map->point_start.x + 0.5;
	data->player.pos.y = map->point_start.y + 0.5;
	data->player.dir.x = 0;
	data->player.dir.y = 0;
	data->player.plane.x = 0;
	data->player.plane.y = 0;
	data->screen.img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data->screen.img)
		return (0);
	data->screen.addr = (int *)mlx_get_data_addr(data->screen.img,
			&data->screen.bpp, &data->screen.size, &data->screen.endian);
	data->rot_speed = 0.06;
	data->move_speed = 0.05;
	init_positions(data);
	ft_memset(&data->keys, 0, sizeof(t_key_info));
	return (1);
}

int	run(t_map *map)
{
	t_data		data;

	data.mlx = mlx_init();
	if (!data.mlx && !fatal_error("MLX init failed"))
		return (EXIT_FAILURE);
	if (!init_data(&data, map) && !fatal_error("Initialization failed")
		&& free_exit(&data))
		return (EXIT_FAILURE);
	if (!load_textures(&data) && free_exit(&data))
		return (EXIT_FAILURE);
	data.win = mlx_new_window(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	mlx_hook(data.win, 2, 1L << 0, &key_pressed_hook, &data);
	mlx_hook(data.win, 3, 1L << 1, &key_released_hook, &data);
	mlx_hook(data.win, 17, 0, &mlx_loop_end, data.mlx);
	mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_loop(data.mlx);
	free_exit(&data);
	return (EXIT_SUCCESS);
}
