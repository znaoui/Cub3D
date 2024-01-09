/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:20:33 by cdudzik           #+#    #+#             */
/*   Updated: 2023/01/22 02:40:59 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

int	ft_isspace(char c);

char	*trim_start(char *str)
{
	if (str)
	{
		while (*str && ft_isspace(*str))
			str++;
	}
	return (str);
}

int	free_all(void *o1, void *o2)
{
	if (o1)
		free(o1);
	if (o2)
		free(o2);
	return (1);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	free_map(t_map	*map)
{
	int	i;

	if (map)
	{
		i = -1;
		if (map->grid)
		{
			while (++i < map->height)
				free(map->grid[i]);
			free(map->grid);
		}
		if (map->textures)
			free_textures(map->textures);
		free(map);
	}
	return (1);
}
