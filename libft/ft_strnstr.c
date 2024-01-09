/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:28:50 by cdudzik           #+#    #+#             */
/*   Updated: 2021/11/26 15:22:41 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*start;
	size_t	index;
	size_t	i;

	if (!(*little))
		return ((char *)(big));
	i = 0;
	while (i < len && big[i])
	{
		if (big[i] == *little)
		{
			index = 0;
			start = (char *)&big[i];
			while ((i + index) < len && little[index] && big[i + index]
				&& big[i + index] == little[index])
				index++;
			if (little[index] == 0)
				return (start);
		}
		i++;
	}
	return (NULL);
}
