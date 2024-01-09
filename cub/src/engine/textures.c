/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:23:34 by cdudzik           #+#    #+#             */
/*   Updated: 2023/01/25 15:30:24 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"
#include "mlx.h"
#include "libft.h"

int	load_texture(t_data *data, char *path, int **texture)
{
	int		height;
	int		width;
	t_img	img;
	int		y;
	int		x;

	if (DEBUG)
		printf("[DEBUG] load_texture %s\n", path);
	img.img = mlx_xpm_file_to_image(data->mlx, path, &width, &height);
	if (!img.img)
		return (fatal_error_i2("Could not load texture ", path));
	img.addr = (int *)mlx_get_data_addr(img.img, &img.bpp,
			&img.size, &img.endian);
	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
			(*texture)[width * y + x] = img.addr[width * y + x];
	}
	mlx_destroy_image(data->mlx, img.img);
	return (1);
}

int	load_rgb(int **rgb)
{
	if (DEBUG)
		printf("[DEBUG] load_rbg %d,%d,%d\n", (*rgb)[0], (*rgb)[1], (*rgb)[2]);
	(*rgb)[0] = (1 << 24 | (*rgb)[0] << 16 | (*rgb)[1] << 8 | (*rgb)[2]);
	return (1);
}

int	load_textures(t_data *data)
{
	int	i;

	data->textures = (int **)malloc(sizeof(int *) * 4);
	if (!data->textures)
		return (fatal_error_i("Textures allocation failed"));
	i = -1;
	while (++i < 4)
	{
		data->textures[i] = (int *)ft_calloc(sizeof(int),
				(TEXTURE_HEIGHT * TEXTURE_WIDTH));
		if (!data->textures[i])
			return (fatal_error_i("Textures allocation failed"));
	}
	return (load_texture(data, data->map->textures->no, &data->textures[0])
		&& load_texture(data, data->map->textures->so, &data->textures[1])
		&& load_texture(data, data->map->textures->ea, &data->textures[2])
		&& load_texture(data, data->map->textures->we, &data->textures[3])
		&& load_rgb(&data->map->textures->floor)
		&& load_rgb(&data->map->textures->ceiling));
}
