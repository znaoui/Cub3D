/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:51:29 by cdudzik           #+#    #+#             */
/*   Updated: 2023/02/02 14:59:13 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define DEBUG 0

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

# include <stdlib.h>

typedef enum s_cell_type
{
	FREE,
	WALL,
	VOID,
	START_NORTH,
	START_EAST,
	START_WEST,
	START_SOUTH,
	UNKNOWN_CELL
}	t_cell_type;

typedef struct s_point_i
{
	int	x;
	int	y;
}	t_point_i;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_raycast_vars
{
	t_point_i	coords;
	t_point		ray_dir;
	t_point		step;
	t_point_i	map;
	t_point		side_dist;
	t_point		delta_dist;
	double		perp_wall_dist;
	int			draw_start;
	int			draw_end;
	int			side;
}	t_raycast_vars;

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		*ceiling;
	int		*floor;
}	t_textures;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bpp;
	int		size;
	int		endian;
}	t_img;

typedef struct s_key_info
{
	int	forward_pressed;
	int	backward_pressed;
	int	left_pressed;
	int	right_pressed;
	int	rotate_left_pressed;
	int	rotate_right_pressed;
}	t_key_info;

typedef struct s_player
{
	t_point	pos;
	t_point	dir;
	t_point	plane;
}	t_player;

typedef struct s_map
{
	int			**grid;
	int			height;
	int			width;
	t_point		point_start;
	t_cell_type	orientation_start;
	t_textures	*textures;
}	t_map;

typedef struct s_data
{
	t_map		*map;
	t_player	player;
	void		*mlx;
	void		*win;
	int			**textures;
	t_img		screen;
	double		move_speed;
	double		rot_speed;
	t_key_info	keys;
}	t_data;

t_map	*parse_cub_file(const char *name);
int		free_map(t_map	*map);
int		run(t_map *map);
void	*fatal_error(const char *s1);
int		fatal_error_i2(const char *s1, const char *s2);
int		fatal_error_i(const char *s1);
int		free_a(void *o1);
int		free_exit(t_data *data);

#endif
