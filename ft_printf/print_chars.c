/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:22:40 by anikitin          #+#    #+#             */
/*   Updated: 2024/07/17 14:01:25 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

ssize_t	ft_putstr(char *s)
{
	ssize_t	len;

	if (!s)
	{
		if (ft_putstr("(null)") < 0)
			return (-1);
		return (6);
	}
	len = 0;
	while (*s)
	{
		if (ft_putchar(*s) < 0)
			return (-1);
		len++;
		s++;
	}
	return (len);
}
