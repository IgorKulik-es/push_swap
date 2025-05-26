/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:13:46 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/21 16:04:43 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		diff;
	size_t	index;

	diff = 0;
	index = 0;
	while (*s1 && *s2 && index < n)
	{
		if (*s1 != *s2)
		{
			diff = (unsigned char)*s1 - (unsigned char)*s2;
			return (diff);
		}
		s1++;
		s2++;
		index++;
	}
	if (index < n)
		diff = (unsigned char)*s1 - (unsigned char)*s2;
	return (diff);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	length;

	length = 0;
	index = 0;
	while (src[length])
		length++;
	if (size > 0)
	{
		while (src[index] && (index < size - 1))
		{
			dst[index] = src[index];
			index++;
		}
		dst[index] = '\0';
	}
	return (length);
}

void	clean_split(char **arr, int words)
{
	words--;
	while (words >= 0)
	{
		free(arr[words]);
		words--;
	}
	free(arr);
}
