/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:35:59 by cdudzik           #+#    #+#             */
/*   Updated: 2023/02/02 16:15:35 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

int	try_assign_start(t_map *map, t_cell_type type, int x)
{
	if (type == START_NORTH || type == START_SOUTH
		|| type == START_EAST || type == START_WEST)
	{
		if (map->orientation_start != UNKNOWN_CELL)
			return (0);
		map->orientation_start = type;
		map->point_start.x = map->height;
		map->point_start.y = x;
	}
	return (1);
}

void	free_ml(void *o)
{
	t_map_line	*line;

	line = o;
	if (line)
	{
		if (line->line)
			free(line->line);
		free(line);
	}
}

int	free_lns(void *o, t_list *list)
{
	if (o)
		free(o);
	if (list)
		ft_lstclear(&list, free_ml);
	return (1);
}

t_cell_type	get_cell_type(char c)
{
	if (c == ' ')
		return (VOID);
	else if (c == '0')
		return (FREE);
	else if (c == '1')
		return (WALL);
	else if (c == 'N')
		return (START_NORTH);
	else if (c == 'S')
		return (START_SOUTH);
	else if (c == 'E')
		return (START_EAST);
	else if (c == 'W')
		return (START_WEST);
	return (UNKNOWN_CELL);
}

t_map	*init_map(t_list **list)
{
	t_map	*map;

	*list = NULL;
	map = (t_map *)malloc(sizeof(t_map));
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->textures = NULL;
	map->orientation_start = UNKNOWN_CELL;
	map->point_start.x = 0;
	map->point_start.y = 0;
	return (map);
}
