/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 08:23:41 by smoore            #+#    #+#             */
/*   Updated: 2023/11/15 13:32:14 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	find_len(const char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	int		l;

	if (s == NULL)
		return (NULL);
	l = find_len(s);
	ch = (char)c;
	while (l >= 0)
	{
		if (s[l] == ch)
		{
			return ((char *)&s[l]);
		}
		l--;
	}
	return (NULL);
}
