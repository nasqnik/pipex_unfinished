/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:16:49 by anikitin          #+#    #+#             */
/*   Updated: 2024/07/10 13:04:14 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		size;
	char	*buffer;

	size = 0;
	size = ft_strlen(s1) + 1;
	buffer = malloc(size * sizeof(char));
	if (!(buffer))
		return (NULL);
	buffer = ft_memcpy(buffer, s1, size);
	return (buffer);
}
