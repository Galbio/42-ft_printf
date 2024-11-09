/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:42:46 by gakarbou          #+#    #+#             */
/*   Updated: 2024/11/09 21:32:21 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

void			init_flags(int *flags);
void			ft_get_bonus_flags(char *str, int *flags, va_list args);

int				ft_atoi(char *str);
int				ft_strlen(char *str);
int long		ft_max(int a, int b);
int	long			ft_min(int a, int b);
unsigned int	ft_log(int long nb, int base);

void			ft_putnbr_times(int long nb, int len);
void			ft_putaddr_times(unsigned long nb, int len, char *base);

int				ft_write_and_return(char c, int ret);
int				ft_write_integer(int nb, int *flags, size_t res);
int				ft_write_unsigned(unsigned int nb, int *flags);
int				ft_write_addr(unsigned long addr, int *flags);
int				ft_write_char(int c, int *flags);
int				ft_hex(unsigned int hex, int *flags, char *base);
int				ft_write_string(char *str, int *flags);

#endif