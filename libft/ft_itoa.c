/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:16:03 by anikitin          #+#    #+#             */
/*   Updated: 2024/07/10 13:24:07 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	char_counter(int n)
{
	size_t	counter;

	counter = 0;
	if (n < 0)
	{
		n = (n / 10) * -1;
		counter += 2;
	}
	while (n > 0)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}

static size_t	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

static int	create_string(char *str, int n)
{
	int	i;

	i = 0;
	if (n / 10 != 0)
		i = create_string(str, n / 10);
	else if (n < 0)
	{
		str[i] = '-';
		i++;
	}
	str[i] = ft_abs(n % 10) + '0';
	i++;
	str[i] = '\0';
	return (i);
}

char	*ft_itoa(int n)
{
	char	*number;
	int		len;

	len = char_counter(n);
	if (len == 0)
		len = 1;
	number = (char *)malloc((len + 1) * sizeof(char));
	if (!number)
		return (NULL);
	create_string(number, n);
	return (number);
}
