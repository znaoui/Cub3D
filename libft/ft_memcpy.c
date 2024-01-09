/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:38:04 by cdudzik           #+#    #+#             */
/*   Updated: 2021/11/29 12:20:11 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			index;
	unsigned char	*bsrc;
	unsigned char	*bdst;

	if (!dest && !src)
		return (NULL);
	index = 0;
	bsrc = (unsigned char *)src;
	bdst = (unsigned char *)dest;
	while (index < n)
	{
		bdst[index] = bsrc[index];
		index++;
	}
	return (dest);
}
