/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:04:03 by cdudzik           #+#    #+#             */
/*   Updated: 2021/11/26 15:01:43 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			index;
	unsigned char	*tmp;

	tmp = (unsigned char *)s;
	index = 0;
	while (index < n)
		tmp[index++] = (unsigned char)c;
	return (s);
}
