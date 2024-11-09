/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:55:22 by gakarbou          #+#    #+#             */
/*   Updated: 2024/11/09 21:56:03 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

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
