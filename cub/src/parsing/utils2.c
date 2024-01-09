/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:14:38 by cdudzik           #+#    #+#             */
/*   Updated: 2023/01/23 17:02:05 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parsing.h"
#include "libft.h"

int		ft_isspace(char c);

int	is_valid_int(char *str)
{
	char	*tmp;
	int		i;

	tmp = str;
	if (*tmp == '-' || *tmp == '+')
		tmp++;
	while (*tmp && ft_isdigit(*tmp))
		tmp++;
	while (*tmp && ft_isspace(*tmp))
		tmp++;
	if (*tmp != 0)
		return (0);
	i = ft_atoi(str);
	tmp = ft_itoa(i);
	if (tmp != NULL)
	{
		if ((*str == '+' && i >= 0) || (i == 0 && *str == '-'))
			str++;
		while (i != 0 && *str == '0')
			str++;
		i = ft_strncmp(tmp, str, ft_strlen(tmp)) == 0;
		free(tmp);
		return (i);
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2++)
		if (*s1++ == 0)
			return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)--s2);
}

int	free_textures(t_textures *textures)
{
	if (textures)
	{
		if (textures->no)
			free(textures->no);
		if (textures->so)
			free(textures->so);
		if (textures->ea)
			free(textures->ea);
		if (textures->we)
			free(textures->we);
		if (textures->floor)
			free(textures->floor);
		if (textures->ceiling)
			free(textures->ceiling);
		free(textures);
	}
	return (1);
}

int	free_pair(t_pair *pair)
{
	if (pair)
	{
		if (pair->key)
			free(pair->key);
		if (pair->value)
			free(pair->value);
		free(pair);
	}
	return (1);
}

int	ft_null_or_empty(const char *str)
{
	if (str)
	{
		while (*str)
		{
			if (!ft_isspace(*str))
				return (0);
			str++;
		}
	}
	return (1);
}
