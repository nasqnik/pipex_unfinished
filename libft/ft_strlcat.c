/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:41:14 by anikitin          #+#    #+#             */
/*   Updated: 2024/07/10 13:04:45 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	dst_len;
	unsigned int	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	if (dstsize < dst_len)
		return (src_len + dstsize);
	j = dst_len;
	i = 0;
	if (dstsize > 0 && dst_len < dstsize - 1)
	{
		while (src[i] && (dst_len + i < dstsize - 1))
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		dst[j] = '\0';
	}
	return (dst_len + src_len);
}
