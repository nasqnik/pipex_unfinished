/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:37:53 by anikitin          #+#    #+#             */
/*   Updated: 2024/07/17 13:31:40 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_printf(const char *str, ...);
ssize_t	ft_putchar(char c);
ssize_t	ft_putstr(char *s);
ssize_t	ft_puthex(unsigned long long n, char x);
ssize_t	ft_putnbr(long n);
ssize_t	ft_putptr(void *ptr);

#endif