/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:43:29 by smoore            #+#    #+#             */
/*   Updated: 2023/11/05 20:09:29 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*ptr_s;
	char	ch;

	i = 0;
	ptr_s = (char *)s;
	ch = (char)c;
	while (i < n)
	{
		if (ptr_s[i] == ch)
			return ((void *)&ptr_s[i]);
		i++;
	}
	return (NULL);
}
