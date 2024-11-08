/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:39:50 by gakarbou          #+#    #+#             */
/*   Updated: 2024/11/08 04:22:28 by gakarbou         ###   ########.fr       */
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
	else if (*c == '*' && c[-1] != '.' && !flags[7])
		flags[7] = va_arg(args, int);
	else if (*c >= '0' && *c <= '9' && c[-1] != '.' && !flags[7])
		flags[7] = ft_atoi(c);
	else if (*c >= '0' && *c <= '9' && c[-1] == '.')
		flags[8] = ft_atoi(c);
	else if (*c == 42 && c[-1] == '.')
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

int	ft_start_writers(va_list args, int *flags)
{
	if (flags[0] == 'c')
		return (ft_write_char(va_arg(args, int), flags));
	else if (flags[0] == '%')
		return (ft_write_and_return('%', 1));
	else if (flags[0] == 's')
		return (ft_write_string(va_arg(args, char *), flags));
	/*
	else if (flags[0] == 'd' || flags[0] == 'i')
		return (ft_write_integer(va_arg(args, int), flags));
	else if (flags[0] == 'u')
		return (ft_write_unsigned(va_arg(args, unsigned int), flags));
	else if (flags[0] == 'x')
		return (ft_write_hex(va_arg(args, unsigned int), flags, "0123456789abcdef"));
		*/
	return (0);
}

void	init_flags(int *flags)
{
	int	i;

	i = -1;
	while (++i < 9)
		flags[i] = 0;
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
	char	*str = NULL;
	printf("|%010.6s|\n", str);
	ft_printf("|%010.6s|\n", str);
}
