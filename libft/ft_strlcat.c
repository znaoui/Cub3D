/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:41:38 by cdudzik           #+#    #+#             */
/*   Updated: 2021/11/26 15:00:24 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	ft_arr_len(const char *s, size_t maxlen)
{
	size_t	i;

	i = 0;
	while (i < maxlen)
	{
		if (s[i] == 0)
			return (i);
		i++;
	}
	return (maxlen);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	max;

	dstlen = ft_arr_len(dst, size);
	srclen = ft_strlen(src);
	if (dst[dstlen] != 0)
	{
		max = dstlen;
		while (++max < size && *src)
			dst[max] = *(src++);
		dstlen++;
		return (dstlen + srclen - 1);
	}
	else
	{
		dst = &dst[dstlen];
		max = size - dstlen;
		if (max > 0)
			max--;
		while (max-- && *src)
			*(dst++) = *(src++);
		*dst = 0;
		return (dstlen + srclen);
	}
}
