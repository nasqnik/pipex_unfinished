/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:51:12 by anikitin          #+#    #+#             */
/*   Updated: 2024/07/10 14:37:32 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static size_t	word_count(char const *s, char c)
{
	size_t	count;
	size_t	string_marker;

	count = 0;
	string_marker = 0;
	while (*s)
	{
		if (*s != c && string_marker == 0)
		{
			string_marker = 1;
			count++;
		}
		else if (*s == c)
			string_marker = 0;
		s++;
	}
	return (count);
}

static int	create_string(char **array, int position, size_t buffer)
{
	array[position] = malloc(buffer);
	if (!array[position])
	{
		free_array(array);
		return (1);
	}
	return (0);
}

static int	create_array(char **array, char const *s, char c)
{
	size_t	word_len;
	int		i;

	i = 0;
	while (*s)
	{
		word_len = 0;
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
		{
			word_len++;
			s++;
		}
		if (word_len)
		{
			if (create_string(array, i, word_len + 1))
				return (1);
			ft_strlcpy(array[i], s - word_len, word_len + 1);
			i++;
		}
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	word_counter;

	if (!s)
		return (NULL);
	word_counter = word_count(s, c) + 1;
	array = (char **)malloc((word_counter) * sizeof(char *));
	if (!array)
		return (NULL);
	array[word_counter - 1] = NULL;
	if (create_array(array, s, c) == 1)
		return (NULL);
	return (array);
}
