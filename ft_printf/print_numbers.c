/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:46:33 by anikitin          #+#    #+#             */
/*   Updated: 2024/07/17 14:28:32 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_puthex(unsigned long long n, char x)
{
	ssize_t	len;
	ssize_t	temp;
	char	*base;

	len = 0;
	if (x == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (n > 15)
	{
		temp = ft_puthex((n / 16), x);
		if (temp < 0)
			return (-1);
		len += temp;
	}
	if (ft_putchar(base[n % 16]) < 0)
		return (-1);
	len += 1;
	return (len);
}

ssize_t	ft_putnbr(long n)
{
	ssize_t	len;
	ssize_t	temp;
	char	last_char;

	len = 0;
	if (n < 0)
	{
		if (ft_putchar('-') < 0)
			return (-1);
		len += 1;
		n *= -1;
	}
	last_char = n % 10 + '0';
	if (n > 9)
	{
		temp = ft_putnbr(n / 10);
		if (temp < 0)
			return (-1);
		len += temp;
	}
	if (ft_putchar(last_char) < 0)
		return (-1);
	len += 1;
	return (len);
}

ssize_t	ft_putptr(void *ptr)
{
	ssize_t	len;
	ssize_t	temp;

	if (ft_putstr("0x") < 0)
		return (-1);
	len = 2;
	temp = ft_puthex((unsigned long long)ptr, 'x');
	if (temp < 0)
		return (-1);
	len += temp;
	return (len);
}
