/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:31:17 by smoore            #+#    #+#             */
/*   Updated: 2025/01/05 07:54:11 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_count_sign(const char *str, int *ptr_i)
{
	int	count;
	int	i;

	i = 0;
	count = 1;
	while (str[i] >= 9 && (str[i] <= 13 || str[i] == 32))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			count = -1;
		i++;
	}
	*ptr_i = i;
	return (count);
}

long long	ft_atol(const char *str)
{
	int			sign;
	long long	ans;
	int			i;

	ans = 0;
	sign = ft_count_sign(str, &i);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		ans *= 10;
		ans += str[i] - '0';
		i++;
	}
	return (sign * ans);
}
