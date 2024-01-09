/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:53:40 by cdudzik           #+#    #+#             */
/*   Updated: 2023/01/16 02:32:08 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "cub3d.h"
#include "parsing.h"
#include "libft.h"

int		free_lns(void *o, t_list *list);
t_map	*init_map(t_list **list);
int		is_start_cell(t_cell_type type);
int		try_assign_start(t_map *map, t_cell_type type, int x);

t_map_line	*parse_map_line(char *str, t_map *map)
{
	t_map_line	*ml;
	t_cell_type	type;
	int			i;

	ml = (t_map_line *)malloc(sizeof(t_map_line));
	if (!ml)
		return (NULL);
	str = trim_end(str);
	ml->size = ft_strlen(str);
	ml->line = (int *)malloc(sizeof(int) * ml->size);
	i = -1;
	while (*str && *str != '\n')
	{
		type = get_cell_type(*str);
		if (!try_assign_start(map, type, i + 1) && free_map_line(ml))
			return (parsing_error_null("Multiple starting positions", NULL));
		if (type != UNKNOWN_CELL)
			ml->line[++i] = (int)type;
		else if (free_map_line(ml))
			return (parsing_error_null("Invalid map cell: ", &(*str)));
		str++;
	}
	return (ml);
}

int	push_ml(t_map *map, t_list **list, t_map_line *line)
{
	t_list	*new;

	new = ft_lstnew(line);
	if (!new)
	{
		free_map_line(line);
		return (0);
	}
	map->height++;
	map->width = max(line->size, map->width);
	ft_lstadd_back(list, new);
	return (1);
}

void	fill_lines(t_map *map, t_list *list)
{
	t_list		*tmp;
	t_map_line	*ml;
	int			*new;
	int			i;

	tmp = list;
	while (tmp != NULL)
	{
		ml = tmp->content;
		if (ml->size < map->width)
		{
			i = -1;
			new = (int *)malloc(sizeof(int) * map->width);
			while (++i < ml->size)
				new[i] = ml->line[i];
			free(ml->line);
			while (ml->size < map->width)
				new[++ml->size - 1] = (int)VOID;
			ml->line = new;
		}
		tmp = tmp->next;
	}
}

int	construct_map(t_map *map, t_list *lines)
{
	t_list	*tmp;
	int		i;

	if (!lines)
		return (0);
	fill_lines(map, lines);
	ft_lstiter(lines, &dump_map_line);
	map->grid = (int **)malloc(sizeof(int *) * map->height);
	if (map->grid)
	{
		tmp = lines;
		i = -1;
		while (tmp != NULL)
		{
			map->grid[++i] = ((t_map_line *)tmp->content)->line;
			tmp = tmp->next;
		}
		dump_map(map);
	}
	if (lines)
		ft_lstclear(&lines, &free);
	return (map->grid != NULL);
}

t_map	*parse_map(int fd)
{
	char		*line;
	t_map		*map;
	t_list		*ml_list;
	t_map_line	*ml;

	map = init_map(&ml_list);
	if (!map)
		return (NULL);
	line = read_until_not_empty(fd);
	while (line && !ft_null_or_empty(line))
	{
		ml = parse_map_line(line, map);
		if ((!ml || !push_ml(map, &ml_list, ml))
			&& free_lns(line, ml_list) && free_map(map))
			return (parsing_error_null("Invalid map", NULL));
		free(line);
		line = read_next_line(fd);
	}
	if (ft_null_or_empty(line))
		free_lns(line, NULL);
	line = read_until_not_empty(fd);
	if ((line != NULL || !construct_map(map, ml_list))
		&& free_lns(line, ml_list) && free_map(map))
		return (parsing_error_null("Invalid map", NULL));
	return (map);
}
