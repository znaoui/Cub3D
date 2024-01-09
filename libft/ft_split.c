/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:18:28 by cdudzik           #+#    #+#             */
/*   Updated: 2021/11/29 12:59:03 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_get_char_len(const char *str, char c)
{
	int	count;

	count = 0;
	while (*str && *str != c)
	{
		count++;
		str++;
	}
	return (count);
}

static int	ft_get_arr_len(const char *str, char c)
{
	int		i;
	int		count;
	int		char_len;

	count = 0;
	i = 0;
	if (c == 0)
		return (1);
	while (str[i])
	{
		while (str[i] == c)
			i++;
		char_len = ft_get_char_len(&str[i], c);
		if (char_len)
		{
			count++;
			i += char_len;
		}
	}
	return (count);
}

static void	split(char const *str, char **tokens, int arr_len, char c)
{
	int		char_len;
	int		next;
	int		i;

	i = 0;
	next = 0;
	char_len = 0;
	if (arr_len == 1 && ft_get_char_len(str, c) > 0)
		tokens[next++] = (char *)str;
	while (arr_len > 1 && str[i])
	{
		while (str[i] == c)
			i++;
		char_len = ft_get_char_len(&str[i], c);
		if (char_len)
		{
			tokens[next++] = ft_substr(str, i, char_len);
			i += char_len;
		}
	}
	tokens[next] = 0;
}

char	**ft_split(char const *str, char c)
{
	char	**tokens;
	int		arr_len;

	if (!str)
		return (NULL);
	arr_len = ft_get_arr_len(str, c) + 1;
	tokens = (char **)malloc(arr_len * sizeof(char *));
	if (tokens != NULL)
		split(str, tokens, arr_len, c);
	return (tokens);
}
