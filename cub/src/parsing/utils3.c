/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 13:35:49 by cdudzik           #+#    #+#             */
/*   Updated: 2023/01/15 17:41:19 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

int	ft_isspace(char c);

void	read_to_end(int fd)
{
	char	*line;

	line = read_next_line(fd);
	while (line)
	{
		free(line);
		line = read_next_line(fd);
	}
}

char	*read_until_not_empty(int fd)
{
	char	*line;

	line = read_next_line(fd);
	while (line && ft_null_or_empty(line))
	{
		free(line);
		line = read_next_line(fd);
	}
	return (line);
}

int	free_map_line(t_map_line *line)
{
	if (line)
	{
		if (line->line)
			free(line->line);
		free(line);
	}
	return (1);
}

char	*trim_end(char *s)
{
	char	*back;

	back = s + ft_strlen(s);
	while (ft_isspace(*--back))
		;
	*(back + 1) = '\0';
	return (s);
}

int	str_ends_with(const char *str, const char *suffix)
{
	char	*s;

	s = NULL;
	if (str && suffix)
		s = ft_strnstr(str, suffix, ft_strlen(str));
	return (s && !ft_strcmp(s, suffix));
}
