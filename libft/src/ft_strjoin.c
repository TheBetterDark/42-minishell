/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:45:22 by smoore            #+#    #+#             */
/*   Updated: 2023/11/12 18:06:02 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	find_size(char const *s)
{
	size_t	size;

	size = 0;
	while (s[size] != '\0')
	{
		size++;
	}
	return (size);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	p_l;
	size_t	s_l;
	size_t	i;

	p_l = find_size(s1);
	s_l = find_size(s2);
	ptr = (char *)malloc(p_l + s_l + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < p_l)
	{
		ptr[i] = s1[i];
		i++;
	}
	while (i < p_l + s_l)
	{
		ptr[i] = s2[i - p_l];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
