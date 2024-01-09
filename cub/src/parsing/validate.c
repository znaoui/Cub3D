/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:28:58 by cdudzik           #+#    #+#             */
/*   Updated: 2023/01/30 17:43:27 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "parsing.h"

int	has_path_to_void(t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->grid[y][x] != FREE)
				continue ;
			if ((y > 0 && map->grid[y - 1][x] == VOID)
				|| (y + 1 < map->height && map->grid[y + 1][x] == VOID)
				|| (x > 0 && map->grid[y][x - 1] == VOID)
				|| (x + 1 < map->width && map->grid[y][x + 1] == VOID))
				return (!point_error("Invalid point: ", x, y));
		}
	}
	return (0);
}

int	is_valid_vertical(t_map *map, int x)
{
	int	i;
	int	z;

	i = -1;
	while (++i < map->height && map->grid[i][x] == VOID)
		;
	if (i == map->height)
		return (1);
	if (map->grid[i][x] != WALL)
		return (0);
	z = map->height;
	while (--z > i && map->grid[z][x] == VOID)
		;
	if (map->grid[z][x] != WALL)
		return (0);
	return (1);
}

int	is_valid_horizontal(t_map *map, int y)
{
	int	i;
	int	z;

	i = -1;
	while (++i < map->width && map->grid[y][i] == VOID)
		;
	if (i == map->width)
		return (1);
	if (map->grid[y][i] != WALL)
		return (0);
	z = map->width;
	while (--z > i && map->grid[y][z] == VOID)
		;
	if (z == i || map->grid[y][z] != WALL)
		return (0);
	return (1);
}

int	has_valid_walls(t_map *map)
{
	int	i;

	if (map->height < 3 || map->width < 3)
		return (parsing_error("Invalid walls", NULL));
	i = -1;
	while (++i < map->width)
	{
		if (!is_valid_vertical(map, i))
			return (parsing_error("Invalid walls", NULL));
	}
	i = -1;
	while (++i < map->height)
	{
		if (!is_valid_horizontal(map, i))
			return (parsing_error("Invalid walls", NULL));
	}
	if (has_path_to_void(map))
		return (parsing_error("Found empty space leading to void", NULL));
	return (1);
}

int	validate_map(t_map **map, t_textures *textures)
{
	int	valid;

	(*map)->textures = textures;
	if ((*map)->orientation_start == UNKNOWN_CELL)
		valid = parsing_error("Missing starting position and orientation",
				NULL);
	else
		valid = has_valid_walls(*map);
	if (!valid)
	{
		free_map(*map);
		*map = NULL;
	}
	else
		(*map)->grid[(int)(*map)->point_start.x]
		[(int)(*map)->point_start.y] = FREE;
	return (valid);
}
