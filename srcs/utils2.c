/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:58:18 by gakarbou          #+#    #+#             */
/*   Updated: 2024/11/10 01:50:17 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_write_and_return(char c, int res)
{
	write(1, &c, 1);
	return (res);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	return (res);
}

unsigned int	ft_log(int long nb, int len)
{
	if (nb < 0)
		nb = -nb;
	if (nb < len)
		return (1);
	return (1 + ft_log(nb / len, len));
}

void	ft_putnbr_times(int long nb, int len)
{
	if (!len)
		return ;
	if (nb < 0)
		nb = -nb;
	ft_putnbr_times(nb / 10, len - 1);
	write(1, &("0123456789"[nb % 10]), 1);
}

void	ft_putaddr_times(unsigned long addr, int len, char *base)
{
	if (!len)
		return ;
	ft_putaddr_times(addr / 16, len - 1, base);
	write(1, &(base[addr % 16]), 1);
}
