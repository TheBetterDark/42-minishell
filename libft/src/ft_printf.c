/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:47:05 by smoore            #+#    #+#             */
/*   Updated: 2024/02/15 13:44:01 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	print_c(int c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	print_str(char *str)
{
	if (!str)
		str = "(null)";
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

int	print_int(int num)
{
	int		len;
	char	*c;

	len = 0;
	c = ft_itoa(num);
	len = print_str(c);
	free(c);
	return (len);
}

int	parse_spec(va_list args, const char format)
{
	int	count;

	count = 0;
	if (format == 'c')
		count += print_c(va_arg(args, int));
	else if (format == 's')
		count += print_str(va_arg(args, char *));
	else if (format == 'p')
		count += print_ptr(va_arg(args, unsigned long long));
	else if (format == 'd' || format == 'i')
		count += print_int(va_arg(args, int));
	else if (format == 'u')
		count += print_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		count += print_hex(va_arg(args, unsigned int), format);
	else if (format == '%')
		count += print_c('%');
	return (count);
}

int	ft_printf(const char *f_str, ...)
{
	va_list	args;
	int		count;
	int		i;

	count = 0;
	i = 0;
	va_start(args, f_str);
	while (f_str[i])
	{
		if (f_str[i] == '%')
		{
			count += parse_spec(args, f_str[i + 1]);
			i++;
		}
		else
			count += print_c(f_str[i]);
		i++;
	}
	va_end(args);
	return (count);
}
