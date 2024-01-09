/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:51:19 by cdudzik           #+#    #+#             */
/*   Updated: 2023/01/31 15:35:21 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"
#include "libft.h"

int	main(int argc, char **argv)
{
	t_map	*map;
	int		ret;

	ret = EXIT_FAILURE;
	if (argc != 2)
	{
		ft_putstr_fd("Invalid number of arguments\n", 2);
		return (ret);
	}
	map = parse_cub_file(argv[1]);
	if (map)
		ret = run(map);
	free_map(map);
	return (ret);
}
