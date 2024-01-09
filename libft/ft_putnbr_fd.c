/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:33:57 by cdudzik           #+#    #+#             */
/*   Updated: 2021/11/24 18:38:51 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	unb;

	if (n < 0)
	{
		n *= -1;
		ft_putchar_fd('-', fd);
	}
	unb = n;
	if (unb > 9)
	{
		ft_putnbr_fd(unb / 10, fd);
		ft_putchar_fd('0' + unb % 10, fd);
	}
	else
		ft_putchar_fd('0' + unb, fd);
}
