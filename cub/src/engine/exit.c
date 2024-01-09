/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:32:23 by cdudzik           #+#    #+#             */
/*   Updated: 2023/01/22 00:22:54 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"
#include "mlx.h"

int	free_exit(t_data *data)
{
	int	i;

	if (DEBUG)
		printf("[DEBUG] free_exit\n");
	if (data->mlx)
	{
		if (data->screen.img)
			mlx_destroy_image(data->mlx, data->screen.img);
		if (data->win)
		{
			mlx_clear_window(data->mlx, data->win);
			mlx_destroy_window(data->mlx, data->win);
		}
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data->textures)
	{
		i = -1;
		while (++i < 4)
			free(data->textures[i]);
		free(data->textures);
	}
	return (1);
}
