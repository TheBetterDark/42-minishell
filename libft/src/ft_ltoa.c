/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:52:56 by smoore            #+#    #+#             */
/*   Updated: 2025/01/05 07:55:16 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	get_digits(int n)
{
	int	digits;

	digits = 0;
	if (n < 0)
		digits++;
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	if (digits == 0)
		digits++;
	return (digits);
}

static void	put_arr(char **str, long long n, int i)
{
	if (n == LLONG_MIN)
	{
		ft_strlcpy(*str, "-9223372036854775808", 21);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		(*str)[0] = '-';
	}
	if (n >= 10)
		put_arr(str, n / 10, i - 1);
	(*str)[i] = '0' + (n % 10);
}

char	*ft_ltoa(long long n)
{
	long long	digits;
	char		*ans;

	digits = get_digits(n);
	ans = malloc(digits + 1);
	if (!ans)
		return (0);
	ans[digits] = 0;
	put_arr(&ans, n, digits - 1);
	return (ans);
}
