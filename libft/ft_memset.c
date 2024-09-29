/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:27:09 by anikitin          #+#    #+#             */
/*   Updated: 2024/07/10 13:03:33 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	value;
	unsigned char	*pointer;

	pointer = (unsigned char *)b;
	value = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		pointer[i] = value;
		i++;
	}
	return (pointer);
}
