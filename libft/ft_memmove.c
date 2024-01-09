/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:45:17 by cdudzik           #+#    #+#             */
/*   Updated: 2021/11/29 12:20:43 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*udst;
	unsigned char	*usrc;

	if (!dest && !src)
		return (NULL);
	if (dest >= src)
	{
		udst = (unsigned char *)dest;
		usrc = (unsigned char *)src;
		while (n--)
			udst[n] = usrc[n];
		return (dest);
	}
	else
		return (ft_memcpy(dest, src, n));
}
