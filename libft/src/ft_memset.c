/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:52:02 by smoore            #+#    #+#             */
/*   Updated: 2024/11/29 17:25:46 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
// memset(&obj, 0, sizeof(CustomType));
void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*ptr_s;

	ptr_s = (char *)s;
	i = 0;
	while (i < n)
	{
		ptr_s[i] = c;
		i++;
	}
	return (s);
}
