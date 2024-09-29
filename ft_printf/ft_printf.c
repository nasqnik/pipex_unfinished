/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:39:24 by anikitin          #+#    #+#             */
/*   Updated: 2024/07/17 14:27:37 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static ssize_t	printer(va_list args, const char c)
{
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_putptr(va_arg(args, void *)));
	else if (c == 'i' || c == 'd')
		return (ft_putnbr(va_arg(args, int)));
	else if (c == 'u')
		return (ft_putnbr(va_arg(args, unsigned int)));
	else if (c == 'x' || c == 'X')
		return (ft_puthex(va_arg(args, unsigned int), c));
	else if (c == '%')
		return (ft_putchar('%'));
	return (-1);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	ssize_t	len;
	ssize_t	temp;

	va_start(args, str);
	len = 0;
	while (*str)
	{
		if (*str == '%')
		{
			temp = printer(args, *(++str));
			if (temp < 0)
				return (-1);
			len += temp;
		}
		else
		{
			if (ft_putchar(*str) < 0)
				return (-1);
			len++;
		}
		str++;
	}
	va_end(args);
	return (len);
}
