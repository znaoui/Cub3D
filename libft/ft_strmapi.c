/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmapi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:01:00 by cdudzik           #+#    #+#             */
/*   Updated: 2021/11/26 16:28:04 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ret;
	size_t	i;

	if (!s || !f)
		return (NULL);
	i = 0;
	ret = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (ret != NULL)
	{
		while (s[i] != 0)
		{
			ret[i] = (*f)(i, s[i]);
			i++;
		}
		ret[i] = 0;
	}
	return (ret);
}
