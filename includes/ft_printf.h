/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:42:46 by gakarbou          #+#    #+#             */
/*   Updated: 2024/11/09 22:04:18 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

int	ft_putcharf(char c);
int	ft_putstrf(char *str);
int	ft_putnbrf(int long nb);
int	ft_putaddr(unsigned long int addr);
int	ft_puthex(unsigned long int hex, char *base);

#endif
