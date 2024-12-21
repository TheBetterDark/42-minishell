/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 11:33:17 by smoore            #+#    #+#             */
/*   Updated: 2024/02/15 13:47:31 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	find_hex_len(unsigned int num)
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

static void	put_hex(unsigned int num, const char f_char )
{
	if (num >= 16)
	{
		put_hex(num / 16, f_char);
		put_hex(num % 16, f_char);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
		{
			if (f_char == 'x')
				ft_putchar_fd((num - 10 + 'a'), 1);
			else if (f_char == 'X')
				ft_putchar_fd((num - 10 + 'A'), 1);
		}
	}
}

int	print_hex(unsigned int num, char f_char)
{
	if (num == 0)
		return (write(1, "0", 1));
	else
		put_hex(num, f_char);
	return (find_hex_len(num));
}
