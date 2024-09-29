/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:23:24 by anikitin          #+#    #+#             */
/*   Updated: 2024/07/10 13:04:36 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	unsigned int	s1_size;
	unsigned int	s2_size;

	if (!s1 && !s2)
		return (NULL);
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	str = (char *)malloc((s1_size + s2_size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, s1_size);
	ft_memcpy(str + s1_size, s2, s2_size);
	str[s1_size + s2_size] = '\0';
	return (str);
}
