/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:13:46 by cdudzik           #+#    #+#             */
/*   Updated: 2023/01/19 00:51:10 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parsing.h"

void	dump_map(t_map *map)
{
	int	i;
	int	z;

	if (!DEBUG || !map)
		return ;
	i = -1;
	printf("[DEBUG] Map: height %d width %d start (%f, %f)\n",
		map->height, map->width, map->point_start.x, map->point_start.y);
	while (++i < map->height)
	{
		printf("[DEBUG] ");
		z = -1;
		while (++z < map->width)
			printf("%d", map->grid[i][z]);
		printf("\n");
	}
}

void	dump_map_line(void *o)
{
	int			i;
	t_map_line	*line;

	if (!DEBUG)
		return ;
	line = (t_map_line *)o;
	if (line)
	{
		printf("[DEBUG] Map line dump (%p size %d): ", line->line, line->size);
		i = -1;
		while (++i < line->size)
			printf("%d", line->line[i]);
		printf("\n");
	}
	else
		printf("[DEBUG] Map line is NULL\n");
}
