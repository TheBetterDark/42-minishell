/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:28:31 by smoore            #+#    #+#             */
/*   Updated: 2023/11/15 15:19:40 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	find_len(const char *str)
{
	size_t	l;

	l = 0;
	while (str[l] != '\0')
		l++;
	return (l);
}

size_t	ft_strlcat(char *dst, const char *src, size_t buf)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] && i < buf)
		i++;
	while (src[j] && i + j + 1 < buf)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < buf)
	{
		dst[i + j] = '\0';
	}
	return (i + find_len(src));
}
