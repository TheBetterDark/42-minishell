/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:43:03 by smoore            #+#    #+#             */
/*   Updated: 2024/02/15 13:49:03 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	find_ulen(unsigned int n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static char	*ft_uitoa(unsigned int n)
{
	long	len;
	char	*str;

	if (n == 0)
		len = 1;
	else
		len = find_ulen(n);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	while (len > 0)
	{
		str[len - 1] = n % 10 + '0';
		n /= 10;
		len--;
	}
	return (str);
}

int	print_unsigned(unsigned int num)
{
	int		len;
	char	*c;

	len = 0;
	if (num == 0)
		len += write(1, "0", 1);
	else
	{
		c = ft_uitoa(num);
		len += print_str(c);
		free(c);
	}
	return (len);
}
