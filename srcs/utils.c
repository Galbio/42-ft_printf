/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:47:50 by gakarbou          #+#    #+#             */
/*   Updated: 2024/11/10 01:29:46 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int long	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

unsigned int	ft_unsigned_log(unsigned int long nb)
{
	if (nb < 16)
		return (1);
	return (1 + ft_unsigned_log(nb / 16));
}

int long	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
