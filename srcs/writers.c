/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 21:54:28 by gakarbou          #+#    #+#             */
/*   Updated: 2024/11/09 22:14:41 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putcharf(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putnbrf(int long nb)
{
	if (nb < 0)
	{
		write(1, "-", 1);
		return (1 + ft_putnbrf(-nb));
	}
	if (nb >= 10)
		return (1 + ft_putnbrf(nb / 10));
	return (ft_putcharf((nb % 10) + '0'));
}

int	ft_putstrf(char *str)
{
	if (!str)
		return (ft_putstrf("(null)"));
	if (!(*str))
		return (0);
	write(1, str++, 1);
	return (1 + ft_putstrf(str));
}

int	ft_puthex(unsigned int long hex, char *base, int *res)
{
	if (hex >= 16)
		ft_puthex(hex / 16, base, res);
	*res += 1;
	return (ft_putcharf(base[hex % 16]));
}

int	ft_putaddr(unsigned long int addr)
{
	int	res;

	if (!addr)
		return (ft_putstrf("(nil)"));
	write(1, "0x", 2);
	res = 0;
	ft_puthex(addr, "0123456789abcdef",  &res);
	return (2 + res);
}
