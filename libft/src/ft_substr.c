/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:17:10 by smoore            #+#    #+#             */
/*   Updated: 2023/11/17 14:45:31 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static unsigned int	len_of(char const *s)
{
	unsigned int	l;

	l = 0;
	while (s[l] != '\0')
	{
		l++;
	}
	return (l);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	if (start > len_of(s))
		return (ft_strdup(""));
	if (len_of(s) - start < len)
		len = len_of(s) - start;
	substr = (char *)malloc(len + 1);
	i = 0;
	while (s[start] != '\0' && i < len)
	{
		substr[i] = s[start];
		i++;
		start++;
	}
	substr[i] = '\0';
	return (substr);
}
