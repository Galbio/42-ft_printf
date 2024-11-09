/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 21:40:06 by gakarbou          #+#    #+#             */
/*   Updated: 2024/11/09 22:17:02 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_start_hex(unsigned int hex, char *base)
{
	int	res;

	res = 0;
	ft_puthex(hex, base, &res);
	return (res);
}

int	ft_write_arg(char ope, va_list args)
{
	if (ope == 'c')
		return (ft_putcharf(va_arg(args, int)));
	else if (ope == '%')
		return (ft_putcharf('%'));
	else if (ope == 'd' || ope == 'i')
		return (ft_putnbrf(va_arg(args, int)));
	else if (ope == 'u')
		return (ft_putnbrf((int long)va_arg(args, unsigned int)));
	else if (ope == 's')
		return (ft_putstrf(va_arg(args, char *)));
	else if (ope == 'x')
		return (ft_start_hex(va_arg(args, unsigned int), "0123456789abcdef"));
	else if (ope == 'X')
		return (ft_start_hex(va_arg(args, unsigned int), "0123456789ABCDEF"));
	else if (ope == 'p')
		return (ft_putaddr(va_arg(args, unsigned long int)));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		res;
	int		i;

	va_start(args, format);
	i = -1;
	res = 0;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			res += ft_write_arg(format[i + 1], args);
			i++;
		}
		else
		{
			write(1, &(format[i]), 1);
			res++;
		}
	}
	va_end(args);
	return (res);
}

/*
#include <stdio.h>
int	main(void)
{
	ft_printf("This %p is even stranger", (void *)-1);
}
*/
