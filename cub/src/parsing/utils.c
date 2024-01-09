/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:37:08 by cdudzik           #+#    #+#             */
/*   Updated: 2023/01/13 16:23:58 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"
#include "libft.h"

int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}

static char	*get_first_char(char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	if (*str == 0)
		return (NULL);
	return (str);
}

static char	*get_word(char *str, int is_value)
{
	const char	*start;

	if (!str || !(*str) || ft_isspace(*str))
		return (NULL);
	start = str;
	while (*str && !ft_isspace(*str))
		str++;
	while (is_value && *str && *str != '\n')
		str++;
	if ((str - start) != 0)
		return (ft_substr(start, 0, str - start));
	return (NULL);
}

static char	*word_end(char *str)
{
	while (*str && !ft_isspace(*str))
		str++;
	return (str);
}

t_pair	*read_config_line(char *line)
{
	char	*s;
	t_pair	*pair;
	char	*key;
	char	*value;

	s = get_first_char(line);
	if (!s)
		return (NULL);
	key = get_word(s, 0);
	if (!key)
		return (NULL);
	s = get_first_char(word_end(s));
	value = get_word(s, 1);
	pair = (t_pair *)malloc(sizeof(t_pair));
	pair->key = key;
	pair->value = value;
	return (pair);
}
