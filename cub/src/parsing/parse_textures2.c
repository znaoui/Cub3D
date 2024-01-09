/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 18:09:22 by cdudzik           #+#    #+#             */
/*   Updated: 2023/01/15 20:38:40 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

int	parse_rgb(const char *str, int **rgb);

int	check_duplicate(char **field, t_pair *pair, int **rgb)
{
	if ((field && *field != NULL) || (rgb && *rgb != NULL))
		return (parsing_error("Duplicate texture ", pair->key));
	if (field)
		*field = ft_strdup(pair->value);
	if (rgb)
		return (parse_rgb(pair->value, rgb));
	return (1);
}

int	parsed_all_textures(t_textures *textures)
{
	return (textures != NULL && textures->no != NULL && textures->so != NULL
		&& textures->ea != NULL && textures->we != NULL
		&& textures->floor != NULL && textures->ceiling != NULL);
}
