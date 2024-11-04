/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:39:23 by smoore            #+#    #+#             */
/*   Updated: 2024/02/15 13:48:40 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	address_len(uintptr_t num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num /= 16;
	}
	return (len);
}

static void	ft_putaddress(uintptr_t num)
{
	if (num >= 16)
	{
		ft_putaddress(num / 16);
		ft_putaddress(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
			ft_putchar_fd((num - 10 + 'a'), 1);
	}
}

int	print_ptr(unsigned long long ptr)
{
	int	len;

	len = 0;
	if (ptr != 0)
		len += write(1, "0x", 2);
	if (ptr == 0)
		len += write(1, "(nil)", 5);
	else
	{
		ft_putaddress(ptr);
		len += address_len(ptr);
	}
	return (len);
}
