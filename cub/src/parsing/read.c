/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:48:58 by cdudzik           #+#    #+#             */
/*   Updated: 2023/01/11 17:29:46 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "parsing.h"

int	get_new_line_index(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '\n')
			return (i);
		i++;
		str++;
	}
	return (-1);
}

void	strip(char **str, int max)
{
	char	*new;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen(*str);
	if (len != max)
	{
		new = (char *)malloc(sizeof(char) * (len - max + 1));
		while (++i < len - max)
			new[i] = (*str)[i + max];
		new[i] = 0;
		free(*str);
		*str = new;
	}
	else
	{
		free(*str);
		*str = NULL;
	}
}

char	*get_line_from_str(char **str)
{
	int		index;
	char	*line;
	int		i;

	i = -1;
	line = NULL;
	if (*str == NULL || !(*str))
		return (NULL);
	index = get_new_line_index(*str);
	if (index > -1)
	{
		index++;
		line = (char *)malloc(sizeof(char) * (index + 1));
		while (++i < index)
			line[i] = (*str)[i];
		line[i] = 0;
		strip(str, index);
	}
	return (line);
}

char	*append(char *str, char *buffer, int buf_len)
{
	char	*new;
	int		len;
	int		i;
	int		z;

	i = -1;
	z = -1;
	len = 0;
	if (str)
		len = ft_strlen(str);
	new = (char *)malloc(sizeof(char) * (len + buf_len + 1));
	while (++i < len)
		new[i] = str[i];
	while (++z < buf_len)
		new[i++] = buffer[z];
	new[i] = 0;
	if (str)
		free(str);
	return (new);
}

char	*read_next_line(int fd)
{
	static char	*str = NULL;
	char		*line;
	int			bytes_read;
	char		buffer[BUFFER_SIZE];

	line = get_line_from_str(&str);
	if (!line)
	{
		bytes_read = read(fd, &buffer, BUFFER_SIZE);
		while (bytes_read > 0 && !line)
		{
			str = append(str, buffer, bytes_read);
			line = get_line_from_str(&str);
			ft_bzero(buffer, BUFFER_SIZE);
			if (!line)
				bytes_read = read(fd, &buffer, BUFFER_SIZE);
		}
	}
	return (line);
}
