/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:39:50 by gakarbou          #+#    #+#             */
/*   Updated: 2024/11/09 20:38:27 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

size_t	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	init_flags(int *flags)
{
	int	i;

	i = -1;
	while (++i < 9)
		flags[i] = 0;
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_return_flag(char c)
{
	const char	*flags = "cspdiuxX%";
	size_t		i;
	int			res;

	i = -1;
	res = 0;
	while (flags[++i])
		if (flags[i] == c)
			res = flags[i];
	return (res);
}

int	ft_write_and_return(char c, int res)
{
	write(1, &c, 1);
	return (res);
}

int	ft_atoi(char *str)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	return (res);
}

void	ft_get_bonus_flags(char *c, int *flags, va_list args)
{
	if (*c == '+')
		flags[1] = 1;
	else if (*c == ' ')
		flags[2] = 1;
	else if (*c == '#')
		flags[3] = 1;
	else if (*c == '-')
		flags[4] = 1;
	else if (*c == '0' && !flags[7] && c[-1] != '.')
		flags[5] = 1;
	else if (*c == '.')
		flags[6] = 1;
	else if (*c == '*' && !flags[6] && !flags[7])
		flags[7] = va_arg(args, int);
	else if (*c >= '0' && *c <= '9' && !flags[6] && !flags[7])
		flags[7] = ft_atoi(c);
	else if (*c >= '0' && *c <= '9' && flags[6] && !flags[8])
		flags[8] = ft_atoi(c);
	else if (*c == 42 && flags[6] && !flags[8])
		flags[8] = va_arg(args, int);
}

int	ft_write_char(int c, int *flags)
{
	int	res;

	res = 0;
	while (!flags[4] && res < (flags[7] - 1))
		res += ft_write_and_return(' ', 1);
	write(1, &c, 1);
	while (flags[4] && res < (flags[7] - 1))
		res += ft_write_and_return(' ', 1);
	return (res + 1);
}

size_t	ft_log(int long nb, size_t len)
{
	if (nb < 0)
		nb = -nb;
	if ((size_t)nb < len)
		return (1);
	return (1 + ft_log(nb / len, len));
}

int	ft_write_string(char *str, int *flags)
{
	size_t	res;
	size_t	len;
	size_t	i;

	if (!str)
	{
		str = "(null)";
		if (flags[6] && flags[8] < 6)
			str = "";
	}
	len = ft_strlen(str);
	if (flags[6])
		len = ft_min(len, flags[8]);
	res = 0;
	i = 0;
	while (!flags[4] && flags[7] && (i < (flags[7] - len)))
		i += ft_write_and_return(' ', 1);
	res += len;
	if (len)
		write(1, str, len);
	while (flags[4] && flags[7] && i < (flags[7] - len))
		i += ft_write_and_return(' ', 1);
	return (res + i);
}

void	ft_putnbr_times(int long nb, size_t len)
{
	if (!len)
		return ;
	if (nb < 0)
		nb = -nb;
	ft_putnbr_times(nb / 10, len - 1);
	write(1, &("0123456789"[nb % 10]), 1);
}

void	ft_putaddr_times(unsigned long addr, size_t len)
{
	if (!len)
		return ;
	ft_putaddr_times(addr / 16, len - 1);
	write(1, &("0123456789abcdef"[addr % 16]), 1);
}

void	ft_handle_int_flags(int *flags, size_t *len, int nb)
{
	if (flags[6])
		*len = ft_max(*len, flags[8]);
	if (flags[6] && !flags[8] && !nb)
		*len = 0;
	if ((flags[6] || flags[4]) && flags[5])
		flags[5] = 0;
	if (flags[1] && flags[2])
		flags[2] = 0;
}

int	ft_write_integer(int nb, int *flags, size_t res)
{
	size_t	len;

	len = ft_log(nb, 10);
	ft_handle_int_flags(flags, &len, nb);
	if (nb >= 0 && flags[2])
		res += ft_write_and_return(' ', 1);
	while (!flags[4] && flags[7] && !flags[5] && (len + res
			+ (nb < 0 || flags[1] || (nb >= 0 && flags[2]))) < (size_t)flags[7])
		res += ft_write_and_return(' ', 1);
	if (nb < 0)
		res += ft_write_and_return('-', 1);
	else if (flags[1])
		res += ft_write_and_return('+', 1);
	if (flags[5])
		len = ft_max(flags[7] - res, len);
	ft_putnbr_times(nb, len);
	while (flags[4] && ((len + res) < (size_t)flags[7]))
		res += ft_write_and_return(' ', 1);
	return (res + len);
}

int	ft_write_unsigned(unsigned int nb, int *flags)
{
	size_t	len;
	size_t	res;

	res = 0;
	len = ft_log(nb, 10);
	if (flags[6])
		len = ft_max(len, flags[8]);
	if (flags[6] && !flags[8] && !nb)
		len = 0;
	if ((flags[6] || flags[4]) && flags[5])
		flags[5] = 0;
	while (!flags[4] && flags[7] && !flags[5]
		&& ((len + res) < (size_t)flags[7]))
		res += ft_write_and_return(' ', 1);
	if (flags[5])
		len = ft_max(flags[7] - res, len);
	ft_putnbr_times(nb, len);
	while (flags[4] && ((len + res) < (size_t)flags[7]))
		res += ft_write_and_return(' ', 1);
	return (res + len);
}

int	ft_write_addr(unsigned long addr, int *flags)
{
	int	res;
	int	len;

	if (!addr)
	{
		init_flags(flags);
		write(1, "(nil)", 5);
		return (5);
	}
	res = 0;
	len = ft_log(addr, 16);
	if (flags[6])
		len = ft_max(len, flags[8]);
	if (flags[6] && !flags[8] && !addr)
		len = 0;
	if (flags[1] && flags[2])
		flags[2] = 0;
	if ((flags[6] || (flags[4] && flags[5])))
		flags[5] = 0;
	while (!flags[4] && flags[7] && !flags[5]
		&& (((flags[1] || flags[2]) + res + len + 2) < flags[7]))
		res += ft_write_and_return(' ', 1);
	if (flags[2])
		res += ft_write_and_return(' ', 1);
	else if (flags[1])
		res += ft_write_and_return('+', 1);
	if (flags[5])
		len = ft_max(flags[7] - res, len);
	write(1, "0x", 2);
	ft_putaddr_times(addr, len);
	while (flags[4] && ((len + res + 2) < flags[7]))
		res += ft_write_and_return(' ', 1);
	return (res + len + 2);
}

char	return_x_base(char c)
{
	if (c == 'A')
		write(1, "X", 1);
	else
		write(1, "x", 1);
}

int	ft_write_hexa(unsigned int hex, int *flags, char *base)
{
	int	res;
	int	len;

	len = ft_log(hex, 16);
	flags[1] = 0;
	flags[2] = 0;
	res = (flags[3] * 2);
	if (flags[6])
		len = ft_max(len, flags[8]);
	if (flags[6] && !flags[8] && !hex)
		len = 0;
	while (!flags[4] && flags[7] && !flags[5]
		&& (res + len) < flags[7])
		res += ft_write_and_return(' ', 1);
	if (flags[3])
		write(1, "0", 1);
	if (flags[3])
		return_x_base(base[10]);
	ft_putaddr_times(hex, len);
	while (flags[4] && ((len + res) < flags[7]))
		res += ft_write_and_return(' ', 1);
	return (res + len);
}

int	ft_start_writers(va_list args, int *flags)
{
	if (flags[0] == 'c')
		return (ft_write_char(va_arg(args, int), flags));
	else if (flags[0] == '%')
		return (ft_write_and_return('%', 1));
	else if (flags[0] == 's')
		return (ft_write_string(va_arg(args, char *), flags));
	else if (flags[0] == 'd' || flags[0] == 'i')
		return (ft_write_integer(va_arg(args, int), flags, 0));
	else if (flags[0] == 'u')
		return (ft_write_unsigned(va_arg(args, unsigned int), flags));
	else if (flags[0] == 'p')
		return (ft_write_addr(va_arg(args, unsigned long), flags));
	else if (flags[0] == 'x')
		return (ft_write_hexa(va_arg(args, unsigned int), flags, "0123456789abcdef"));
	return (0);
}

//flags = {char, +, ' ', #, -, 0, ., padding, delim}
int	ft_write_arg(char *str, va_list args)
{
	int	flags[9];
	int	i;

	init_flags(flags);
	i = -1;
	while (!flags[0])
	{
		flags[0] = ft_return_flag(str[++i]);
		ft_get_bonus_flags(str + i, flags, args);
	}
	return (ft_start_writers(args, flags));
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	i;
	int		length;

	length = 0;
	i = -1;
	va_start(args, format);
	while (format[++i])
	{
		if (format[i] == '%')
		{
			length += ft_write_arg((char *)format + i + 1, args);
			i++;
			while (!ft_return_flag((char)format[i]))
				i++;
		}
		else
			length += ft_write_and_return(format[i], 1);
	}
	return (length);
}

#include <stdio.h>
int	main(void)
{
	int	a;
	int	b;
	char	*str = "wwerre";

	a = printf("|%#25.5x|\n", 42);
	b = ft_printf("|%#25.5x|\n", 42);
	printf("%d - %d\n", a, b);
}
