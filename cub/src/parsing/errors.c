/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:09:47 by cdudzik           #+#    #+#             */
/*   Updated: 2023/01/15 19:39:49 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include "libft.h"

void	*parsing_error_null(const char *s1, const char *s2)
{
	ft_putstr_fd("Error parsing map: ", 2);
	if (s1)
		ft_putstr_fd(s1, 2);
	if (s2)
		ft_putstr_fd(s2, 2);
	ft_putstr_fd("\n", 2);
	return (NULL);
}

int	point_error(const char *s1, int x, int y)
{
	ft_putstr_fd("Error parsing map: ", 2);
	if (s1)
		ft_putstr_fd(s1, 2);
	ft_putstr_fd("(", 2);
	ft_putnbr_fd(x, 2);
	ft_putstr_fd(",", 2);
	ft_putnbr_fd(y, 2);
	ft_putstr_fd(")", 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

int	parsing_error(const char *s1, const char *s2)
{
	ft_putstr_fd("Error parsing map: ", 2);
	if (s1)
		ft_putstr_fd(s1, 2);
	if (s2)
		ft_putstr_fd(s2, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

void	*perr_null(void)
{
	perror("Error parsing map");
	return (NULL);
}
