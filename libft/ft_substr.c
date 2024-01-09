/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:45:32 by cdudzik           #+#    #+#             */
/*   Updated: 2021/11/26 16:28:25 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;
	size_t	strlen;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	if (start > strlen)
		len = 0;
	else if (len + start > strlen)
		len = strlen - start;
	ret = (char *)malloc((len + 1) * sizeof(char));
	if (ret != NULL)
	{
		i = 0;
		while (i < len && start < strlen && *s)
		{
			ret[i] = s[start];
			start++;
			i++;
		}
		ret[i] = 0;
	}
	return (ret);
}
