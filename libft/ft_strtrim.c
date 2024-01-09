/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:07:08 by cdudzik           #+#    #+#             */
/*   Updated: 2021/11/26 16:28:10 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_is_in_set(char const *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	start;

	if (!s1)
		return (NULL);
	start = 0;
	len = ft_strlen(s1);
	while (ft_is_in_set(set, s1[start]))
		start++;
	while (s1[start] && ft_is_in_set(set, s1[--len]))
		;
	return (ft_substr(s1, start, (len - start + 1)));
}
