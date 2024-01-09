/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:33:32 by cdudzik           #+#    #+#             */
/*   Updated: 2021/11/29 12:13:31 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_count_digits(int n)
{
	int				count;
	unsigned int	tmp;

	if (n < 0)
		n *= -1;
	tmp = n;
	count = 1;
	while (tmp / 10 != 0)
	{
		count++;
		tmp /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char			*ret;
	int				digits;
	int				negative;
	unsigned int	tmp;

	negative = n < 0;
	digits = ft_count_digits(n);
	ret = (char *)malloc((digits + 1 + negative) * sizeof(char));
	if (ret != NULL)
	{
		if (negative)
		{
			ret[0] = '-';
			n *= -1;
		}
		tmp = n;
		ret[digits + negative] = 0;
		while (digits--)
		{
			ret[digits + negative] = (tmp % 10) + 48;
			tmp /= 10;
		}
	}
	return (ret);
}
