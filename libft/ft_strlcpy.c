/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:09:03 by cdudzik           #+#    #+#             */
/*   Updated: 2021/11/25 14:03:55 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;

	len = ft_strlen(src);
	if (size > 0 && size - 1 >= len)
	{
		ft_memcpy(dst, src, len);
		dst[len] = 0;
	}
	else
	{
		ft_memcpy(dst, src, size);
		if (size > 0)
			dst[size - 1] = 0;
	}
	return (len);
}
