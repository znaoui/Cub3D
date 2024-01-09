/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:20:35 by cdudzik           #+#    #+#             */
/*   Updated: 2023/01/23 17:02:16 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include "cub3d.h"
#include "parsing.h"
#include "libft.h"

int		check_duplicate(char **field, t_pair *pair, int **rgb);
int		parsed_all_textures(t_textures *textures);
void	read_to_end(int fd);
char	*trim_start(char *str);

int	is_valid_rgb_value(const char *start, const char *str, int *val)
{
	char	*sub;
	int		tmp;
	int		ret;

	ret = 1;
	if (str - start > 0)
	{
		sub = ft_substr(start, 0, str - start);
		if (!sub || !is_valid_int(trim_start(sub)))
			ret = parsing_error("Invalid rgb value: ", sub);
		else
		{
			tmp = ft_atoi(sub);
			if (tmp < 0 || tmp > 255)
				ret = parsing_error("Color must be between 0 and 255 : ", sub);
			else
				*val = tmp;
		}
		if (sub)
			free(sub);
	}
	else
		return (parsing_error("Invalid rgb", NULL));
	return (ret);
}

int	parse_rgb(const char *str, int **rgb)
{
	const char	*start;
	int			i;
	int			rgb_tmp[3];

	i = -1;
	ft_memset(rgb_tmp, -1, 3);
	while (++i < 3)
	{
		start = str;
		while (*str && (i == 2 || (i < 2 && *str != ',')))
			str++;
		if (!is_valid_rgb_value(start, str, &rgb_tmp[i]))
			return (0);
		if (*str)
			str++;
	}
	i = -1;
	*rgb = (int *)malloc(sizeof(int) * 3);
	while (++i < 3)
		(*rgb)[i] = rgb_tmp[i];
	return (1);
}

int	assign_texture(t_textures *textures, t_pair *pair)
{
	int	ret;

	ret = 1;
	if (pair == NULL)
		return (parsing_error(NULL, NULL));
	if (ft_null_or_empty(pair->value))
		ret = parsing_error("Value is empty for key ", pair->key);
	else if (!ft_strcmp(pair->key, "NO"))
		ret = check_duplicate(&textures->no, pair, NULL);
	else if (!ft_strcmp(pair->key, "SO"))
		ret = check_duplicate(&textures->so, pair, NULL);
	else if (!ft_strcmp(pair->key, "EA"))
		ret = check_duplicate(&textures->ea, pair, NULL);
	else if (!ft_strcmp(pair->key, "WE"))
		ret = check_duplicate(&textures->we, pair, NULL);
	else if (!ft_strcmp(pair->key, "F"))
		ret = check_duplicate(NULL, pair, &textures->floor);
	else if (!ft_strcmp(pair->key, "C"))
		ret = check_duplicate(NULL, pair, &textures->ceiling);
	else
		ret = parsing_error("Unknown identifier ", pair->key);
	free_pair(pair);
	return (ret);
}

t_textures	*parse_textures(int fd)
{
	char		*line;
	t_textures	*textures;
	t_pair		*pair;

	textures = (t_textures *)malloc(sizeof(t_textures));
	if (!textures)
		return (NULL);
	textures->ceiling = NULL;
	textures->floor = NULL;
	textures->so = NULL;
	textures->no = NULL;
	textures->ea = NULL;
	textures->we = NULL;
	line = read_next_line(fd);
	while (line != NULL)
	{
		pair = read_config_line(line);
		free(line);
		if ((pair && !assign_texture(textures, pair))
			|| parsed_all_textures(textures))
			break ;
		line = read_next_line(fd);
	}
	return (textures);
}

t_map	*parse_cub_file(const char *name)
{
	int			fd;
	t_textures	*textures;
	t_map		*map;

	if (!str_ends_with(name, ".cub"))
		return (parsing_error_null("Map file extension must be '.cub'", NULL));
	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (perr_null());
	textures = parse_textures(fd);
	if ((!textures || !parsed_all_textures(textures))
		&& free_textures(textures) && !close(fd))
		return (parsing_error_null("Missing textures", NULL));
	map = parse_map(fd);
	if (map)
		validate_map(&map, textures);
	else
		free_textures(textures);
	read_to_end(fd);
	close(fd);
	return (map);
}
