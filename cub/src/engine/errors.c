/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:30:24 by cdudzik           #+#    #+#             */
/*   Updated: 2023/01/20 14:55:16 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	fatal_error_i(const char *s1)
{
	ft_putstr_fd("Fatal error: ", 2);
	if (s1)
		ft_putstr_fd(s1, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

void	*fatal_error(const char *s1)
{
	ft_putstr_fd("Fatal error: ", 2);
	if (s1)
		ft_putstr_fd(s1, 2);
	ft_putstr_fd("\n", 2);
	return (NULL);
}

int	fatal_error_i2(const char *s1, const char *s2)
{
	ft_putstr_fd("Fatal error: ", 2);
	if (s1)
		ft_putstr_fd(s1, 2);
	if (s2)
		ft_putstr_fd(s2, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}
