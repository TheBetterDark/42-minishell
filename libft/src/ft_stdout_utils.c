/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdout_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:52:56 by smoore            #+#    #+#             */
/*   Updated: 2025/01/05 07:55:42 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_putnbr(int n, unsigned int *ct)
{
	char	c;

	if (n == -2147483648)
	{
		write(1, "-2", 2);
		*ct += 2;
		ft_putnbr(147483648, ct);
	}
	else if (n < 0)
	{
		write(1, "-", 2);
		*ct += 1;
		ft_putnbr(-1, ct);
	}
	else if (n > 9)
	{
		ft_putnbr(n / 10, ct);
		ft_putnbr(n % 10, ct);
	}
	else
	{
		c = '0' + n;
		write(1, &c, 1);
		*ct += 1;
	}
}

void	ft_putnbr_u(unsigned int n, unsigned int *ct)
{
	char	c;

	if (n > 9)
		ft_putnbr_u(n / 10, ct);
	c = '0' + n % 10;
	write(1, &c, 1);
	*ct += 1;
}

void	ft_putstr(char *s, unsigned int *ct)
{
	unsigned int	i;

	if (s == 0)
	{
		write(1, "(null)", 6);
		*ct += 6;
		return ;
	}
	i = 0;
	while (s[i])
	{
		write(1, s + i, 1);
		*ct += 1;
		i++;
	}
}

void	ft_putchar(char c, unsigned int *ct)
{
	write(1, &c, 1);
	*ct += 1;
}

void	ft_putptr(void *ptr, unsigned int *ct)
{
	if ((unsigned long)ptr > 15)
		ft_putptr((void *)((unsigned long)ptr / 16), ct);
	write(1, &("0123456789abcdef"[(unsigned long)ptr % 16]), 1);
	*ct += 1;
}
